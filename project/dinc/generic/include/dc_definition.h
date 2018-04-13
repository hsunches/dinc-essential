/*
 * MOBRIC CONFIDENTIAL
 * ___________________
 *
 * 2013 Mobric Incorporated
 * All Rights Reserved.
 *
 * NOTICE:
 * All information contained herein is, and remains the property of
 * Mobric Incorporated and its suppliers, if any. Dissemination of this
 * information or reproduction of this material is strictly forbidden unless
 * prior written permission is obtained from Mobric Incorporated.
 *
 */

#ifndef DC_DEFINITION_H
#define DC_DEFINITION_H

#include <stdint.h>

/*
 *	DIN 2 Bytes Report Packet Header (DIN Client & DIN Server)
 *
 *	[0] is DIN Packet Role
 *	[1] is DIN Packet Message
 *
 *  First 2 bits are used to identify this packet includes Location & Unique ID
 *  10 => Location
 *  01 => Unique ID
 *  11 => Both
 *  00 => None
 *
 */
#define DINP_HDR_MASK_LOC			0x80
#define DINP_HDR_MASK_UID			0x40

// DIN Data Collector ID: HEX{80BB0011 ~ 80BB0019}
#define DIN_DC_CUSTOM_BASE			0x80BB0011

 // DINC Custom event: HEX{80AA0401 ~ 80AAFFFF}
#define DIN_MSG_CUSTOM_EVENT_BASE	0x80AA0401

// DIN Packet Message INT{129 ~ 191} = HEX{81 ~ BF}
#define DIN_PACKET_DC_MSG_BASE		0x81

typedef struct 
{
	/*
	 * Description      : Used in DC routine loop
	 * Return Code      : 
	 * Parameters		: 
	 * Reference        : 
	 * Remarks          : This variable will be reset by calling dc_generate_report_interval once it's value become 0.
	 */
	int report_interval_countdown;

	/*
	 * Description      : Get round trip latency value.
	 * Return Code      : Value of round trip latency.
	 * Parameters		: None.
	 * Reference        : 
	 * Remarks          : 
	 */
	uint32_t (*get_dc_latest_round_trip_latency)(void);

	/*
	 * Description      : Pack the header and data body then send to server.
	 * Return Code      : If it succeeds, returns the number of characters sent. If a return code equal to -1 indicates an error.
	 * Parameters		: msg_type - 	Custom defined packet id which start from DIN_PACKET_DC_MSG_BASE, valid range INT{129 ~ 191} = HEX{81 ~ BF}.
	 *                    extra_role - 	Extra information which will be wrapped within header currently support DINP_HDR_MASK_LOC and DINP_HDR_MASK_UID.
	 *					  data -		Collected data array, maximum length 998 bytes. Suggest stay around 512 bytes and separate into multiple packets if collected data is too long.
	 *					  len -			Actual data length.
	 * Reference        : 
	 * Remarks          : 
	 */
	int (*send_dc_report)(const int msg_type, const int extra_role, const uint8_t* data, const int len);

	/*
	 * Description      : Pack the header and connection history data then send to server.
	 * Return Code      : If it succeeds, returns the number of characters sent. If a return code equal to -1 indicates an error.
	 * Parameters		: data -	Collected data array, maximum length 998 bytes. Suggest stay around 512 bytes and separate into multiple packets if collected data is too long.
	 *					  len -		Actual data length.
	 * Reference        : 
	 * Remarks          : 
	 */
	int (*send_dc_connection_history_information)(const uint8_t* data, const int len);

	/*
	 * Description      : Send request for round trip latency.
	 * Return Code      : If it succeeds, returns the number of characters sent. If a return code equal to -1 indicates an error.
	 * Parameters		: None.
	 * Reference        : 
	 * Remarks          : 
	 */
	int (*send_dc_round_trip_latency_request)(void);

} dc_routine_context;

typedef struct 
{
	int 	dc_id;
	char*	dc_ip; 
	int 	dc_port;
	int 	dc_ext_cmd;

	/*
	 * Description      : DC used to generate report interval according to it's own needs.
	 * Return Code      : Value of report interval.
	 * Parameters		: None.
	 * Reference        : 
	 * Remarks          : 
	 */
	int  (*dc_generate_report_interval)(void);
	
	/*
	 * Description      : DC used to doing initialization.
	 * Return Code      : None.
	 * Parameters		: None.
	 * Reference        : 
	 * Remarks          : 
	 */
	void (*dc_init)(void);
	
	/*
	 * Description      : DC used to print it's own information.
	 * Return Code      : None.
	 * Parameters		: None.
	 * Reference        : 
	 * Remarks          : 
	 */
	void (*dc_version)(void);

	/*
	 * Description      : Load configuration settings of DC.
	 * Return Code      : None.
	 * Parameters		: path -	Configuration file path.
	 * Reference        : 
	 * Remarks          : Regard the format of configuration file, you may refer to our sample configuration files.
	 */
	void (*dc_load_config)(const char* path); 

	/*
	 * Description      : Called when DC latency acknowledge received.
	 * Return Code      : If it succeeds returns 0, otherwise return non-zero number.
	 * Parameters		: context -		dc_routine_context object pointer.
	 *					  latency_ms -	Latency in milliseconds.
	 * Reference        : 
	 * Remarks          : 
	 */
	int (*on_check_latency_ack)(dc_routine_context* context, const int latency_ms);
	
	/*
	 * Description      : Called when handover started.
	 * Return Code      : If it succeeds returns 0, otherwise return non-zero number.
	 * Parameters		: timestamp_usec -	Timestamp when handover start in microseconds.
	 * Reference        : 
	 * Remarks          : 
	 */
	int (*on_handover_start)(const int64_t timestamp_usec);

	/*
	 * Description      : Called when handover finished.
	 * Return Code      : If it succeeds returns 0, otherwise return non-zero number.
	 * Parameters		: is_success -		Indicating that if handover succeed.
	 *					  timestamp_usec -	Timestamp when handover ends in microseconds.
	 *					  latency_usec -	Handover latency in microseconds.
	 * Reference        : 
	 * Remarks          : 
	 */
	int (*on_handover_end)(const int is_success, const int64_t timestamp_usec, const int64_t latency_usec);

	/*
	 * Description      : Called when server is found.
	 * Return Code      : If it succeeds returns 0, otherwise return non-zero number.
	 * Parameters		: context -	dc_routine_context object pointer.
	 * Reference        : 
	 * Remarks          : 
	 */
	int (*on_server_lookup_success)(dc_routine_context* context);

	/*
	 * Description      : Called when server lookup failed.
	 * Return Code      : If it succeeds returns 0, otherwise return non-zero number.
	 * Parameters		: context -	dc_routine_context object pointer.
	 * Reference        : 
	 * Remarks          : 
	 */
	int (*on_server_lookup_failed)(dc_routine_context* context);

	/*
	 * Description      : Called when DIN received the register request from DC.
	 * Return Code      : If it succeeds returns 0, otherwise return non-zero number.
	 * Parameters		: context -	dc_routine_context object pointer.
	 *					  latency -	Latency for network searching in milliseconds.
	 * Reference        : 
	 * Remarks          : 
	 */
	int (*on_network_entry_complete)(dc_routine_context* context, const uint32_t latency);

	/*
	 * Description      : Called routinely in second.
	 * Return Code      : If it succeeds returns 0, otherwise return non-zero number.
	 * Parameters		: context -				dc_routine_context object pointer.
	 *					  report_interval -		DC report collected information interval which is defined in configuration file.
	 *					  idle_threshold - 		Threshold to enter network idle status.
	 * Reference        : 
	 * Remarks          : 
	 */
	int (*collect_dc_routine_info)(dc_routine_context* context, const int report_interval, const int idle_threshold);

	/*
	 * Description      : Called when DIN receiving unknown message ID.
	 * Return Code      : If it succeeds returns 0, otherwise return non-zero number.
	 * Parameters		: context -	dc_routine_context object pointer.
	 *					  msg -		Message ID.
	 * Reference        : 
	 * Remarks          : This is a extension mechanism which allow customer to define their own message type. The allowed message range is started from DIN_MSG_CUSTOM_EVENT_BASE
	 *					  and accepted size is 64510.
	 */
	int (*handle_extra_ipc_message)(dc_routine_context* context, const int msg);

} dc_routine_definition;

// dc routine function
/*
 * Description      : This function hold a workflow and let DC go through each stage in it's live cycle.
 * Return Code      : If it succeeds returns 0, otherwise return non-zero number.
 * Parameters		: argc - Argument count.
 *					  argv - Argument vector.
 *					  def -	 Data collector routine definition.
 * Reference        : 
 * Remarks          : 
 */
extern int util_start_dc_routine(int argc, char* argv[], dc_routine_definition* def);

#endif /* DC_DEFINITION_H */