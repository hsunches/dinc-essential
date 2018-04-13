#!/usr/bin/perl
use strict;
use HTTP::Daemon;
use LWP::Simple;

sub proc_req
{
	my $req = shift;
	my $conn = shift;

	print("http://".$conn->sockhost.":".$conn->sockport.$req->uri->path_query."\n");
	
	my $path = $req->uri->path;

	if ($path ne "/cgi-bin/din.cgi")
	{
		$conn->send_error(RC_NOT_FOUND); 
	}
	elsif ($req->method ne "GET")
	{
		$conn->send_error(RC_FORBIDDEN); 
	}
	else
	{
		my $qs = $req->uri->query();
		
		if (!$qs)
		{
			$conn->send_error(RC_BAD_REQUEST);
		}
		else
		{
			my $text = `QUERY_STRING=$qs $ARGV[0] $ARGV[1]`;
			
			$text =~ s/.+\r\n\r\n//;
			
			my $hdr = HTTP::Headers->new();
			my $resp = HTTP::Response->new(RC_OK, "OK", $hdr, $text);

			$conn->send_response($resp);
		}
	}
}

my $daemon;

$SIG{INT} = 'close_daemon';

sub close_daemon
{
	$daemon->close();
}

sub main
{
	$daemon = HTTP::Daemon->new(LocalPort => 8080);

	return if (!$daemon);

	while (my $conn = $daemon->accept())
	{
		my $req = $conn->get_request();

		next if (!$req);
		proc_req($req, $conn);
	}
}

main();

