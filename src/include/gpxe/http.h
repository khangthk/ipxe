#ifndef _GPXE_HTTP_H
#define _GPXE_HTTP_H

/** @file
 *
 * Hyper Text Transport Protocol
 *
 */

#include <stdint.h>
#include <gpxe/tcp.h>
#include <gpxe/async.h>
#include <gpxe/linebuf.h>

/** HTTP default port */
#define HTTP_PORT 80

/** HTTP receive state */
enum http_rx_state {
	HTTP_RX_RESPONSE = 0,
	HTTP_RX_HEADER,
	HTTP_RX_DATA,
	HTTP_RX_DEAD,
};

/**
 * An HTTP request
 *
 */
struct http_request {
	/** Server address */
	struct sockaddr_tcpip server;
	/** Server host name */
	const char *hostname;
	/** Filename */
	const char *filename;
	/** Data buffer to fill */
	struct buffer *buffer;

	/** HTTP response code */
	unsigned int response;
	/** HTTP Content-Length */
	size_t content_length;

	/** Number of bytes already sent */
	size_t tx_offset;
	/** RX state */
	enum http_rx_state rx_state;
	/** Line buffer for received header lines */
	struct line_buffer linebuf;

	/** TCP application for this request */
	struct tcp_application tcp;
	/** Asynchronous operation */
	struct async_operation aop;
};

extern struct async_operation * http_get ( struct http_request *http );

#endif /* _GPXE_HTTP_H */
