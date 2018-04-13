#include <stdio.h>
#include <string.h>
#include "mongoose.h"

#define BUF_SIZE	1024

// This function will be called by mongoose on every new request.
static int begin_request_handler(struct mg_connection *conn) {
	const struct mg_request_info *request_info = mg_get_request_info(conn);
	int content_length;
	char content[BUF_SIZE];

	// Prepare the message we're going to send
	if (strcmp(request_info->request_method, "GET") != 0 ||
		strcmp(request_info->uri, "/cgi-bin/din.cgi") != 0 ||
		request_info->query_string == NULL ||
		strncmp(request_info->query_string, "hal=", 4) != 0) {
		
		// Send HTTP reply to the client
		mg_printf(conn, "HTTP/1.1 404 Not Found\r\n\r\n");
	} else {
		char command[256];
		FILE *pipe;

		sprintf(command, "QUERY_STRING=%s ./din.cgi", request_info->query_string);
		pipe = popen(command, "r");

		if (pipe == NULL) {
			content_length = snprintf(content, sizeof(content), "Failed to create pipe.");
		} else {
			char line[256];

			*content = 0;

			while (fgets(line, sizeof(line), pipe) != NULL) {
				strcat(content, line);
			}

			content_length = strlen(content);
			pclose(pipe);
		}

		// Send HTTP reply to the client
		mg_printf(conn,
			"HTTP/1.1 200 OK\r\n"
			"Content-Length: %d\r\n"        // Always set Content-Length
			"%s",
			content_length, content);
	}

	// Returning non-zero tells mongoose that our function has replied to
	// the client, and mongoose should not send client any more data.
	return 1;
}

int main(void) {
	struct mg_context *ctx;
	struct mg_callbacks callbacks;

	// List of options. Last element must be NULL.
	const char *options[] = {"listening_ports", "8080", NULL};

	// Prepare callbacks structure. We have only one callback, the rest are NULL.
	memset(&callbacks, 0, sizeof(callbacks));
	callbacks.begin_request = begin_request_handler;

	// Start the web server.
	ctx = mg_start(&callbacks, NULL, options);

	// Wait until user hits "enter". Server is running in separate thread.
	// Navigating to http://localhost:8080 will invoke begin_request_handler().
	getchar();

	// Stop the server.
	mg_stop(ctx);

	return 0;
}
