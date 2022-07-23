#[[
IDT4: Unofficial source port for idTech4 based games
Copyright (c) 1999-2011 id Software LLC, a ZeniMax Media company. 
Copyright (c) 2022 Boris I. Bendovsky (bibendovsky@hotmail.com) and Contributors.
SPDX-License-Identifier: GPL-3.0-only AND MIT
]]

cmake_minimum_required(VERSION 3.16.9 FATAL_ERROR)
project(idt4_curl_lib VERSION 1.0.0 LANGUAGES C)

message(STATUS "[${PROJECT_NAME}] Version: ${PROJECT_VERSION}")

add_library(${PROJECT_NAME} STATIC)

set_target_properties(${PROJECT_NAME}
	PROPERTIES
		C_STANDARD 90
		C_STANDARD_REQUIRED ON
		C_EXTENSIONS OFF
)

target_compile_definitions(${PROJECT_NAME}
	PRIVATE
		_USRDLL
		CURLLIB_EXPORTS
)

target_include_directories(${PROJECT_NAME}
	PRIVATE
		./include
)

target_sources(${PROJECT_NAME}
	PRIVATE
		lib/arpa_telnet.h
		lib/base64.c
		lib/base64.h
		lib/connect.c
		lib/connect.h
		lib/cookie.c
		lib/cookie.h
		lib/dict.c
		lib/dict.h
		lib/easy.c
		lib/escape.c
		lib/escape.h
		lib/file.c
		lib/file.h
		lib/formdata.c
		lib/formdata.h
		lib/ftp.c
		lib/ftp.h
		lib/getdate.c
		lib/getdate.h
		lib/getenv.c
		lib/getinfo.c
		lib/hash.c
		lib/hostip.c
		lib/hostip.h
		lib/http.c
		lib/http.h
		lib/http_chunks.c
		lib/http_chunks.h
		lib/http_digest.c
		lib/http_digest.h
		lib/http_ntlm.c
		lib/http_ntlm.h
		lib/if2ip.c
		lib/if2ip.h
		lib/inet_ntoa_r.h
		lib/inet_pton.c
		lib/inet_pton.h
		lib/krb4.c
		lib/krb4.h
		lib/ldap.c
		lib/ldap.h
		lib/llist.c
		lib/md5.c
		lib/md5.h
		lib/memdebug.c
		lib/memdebug.h
		lib/mprintf.c
		lib/multi.c
		lib/netrc.c
		lib/netrc.h
		lib/progress.c
		lib/progress.h
		lib/security.c
		lib/security.h
		lib/sendf.c
		lib/sendf.h
		lib/setup.h
		lib/share.c
		lib/speedcheck.c
		lib/speedcheck.h
		lib/ssluse.c
		lib/ssluse.h
		lib/strequal.c
		lib/strequal.h
		lib/strtok.c
		lib/strtok.h
		lib/telnet.c
		lib/telnet.h
		lib/timeval.c
		lib/timeval.h
		lib/transfer.c
		lib/transfer.h
		lib/url.c
		lib/url.h
		lib/urldata.h
		lib/version.c
	PRIVATE
		lib/libcurl.def
)