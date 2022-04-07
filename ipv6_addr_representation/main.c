#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <stdint.h>
#include <ctype.h>
#include <inttypes.h>
#include <arpa/inet.h>

#define MY_DEBUG 0

#define N_IPV6_BYTES sizeof(struct in6_addr)


/***************************************************************************************/
/**
 * @brief 打印字节流，调试用
 */
void print_byte_stream(uint8_t* data, uint32_t dsize)
{
	if(data == NULL || dsize == 0)
	{
		return;
	}
	
	for(uint32_t idx = 0; idx < dsize; ++idx)
	{
		printf("%02x ", data[idx]);
	}
	
	printf("\n");
}

/**
 * @brief 打印比特流，调试用
 */
void print_binary_stream(uint8_t* data, uint32_t dsize)
{
	if(data == NULL || dsize == 0)
	{
		return;
	}
	
	for(uint32_t idx = 0; idx < dsize; ++idx)
	{
		for(int j = 7; j >= 0; --j)
		{
			uint8_t result = (data[idx] & (0x01 << j));
			
			printf("%d", result != 0);
		}
		
		printf(" ");
	}
	
	printf("\n");
}
/***************************************************************************************/

/**
 * @brief 判断ip地址的合法性
 *
 * @return int
 * @retval -1 不合法
 *         AF_INET || AF_INET6 合法
 */
int is_ip_addr(const char* ip_str)
{
	if(ip_str == NULL || ip_str[0] == '\0')
	{
		return -1;
	}
	
	if( strchr(ip_str, ':') == NULL )
	{
		// ipv4
		struct in_addr addr = {0};
		
		if( inet_pton(AF_INET, ip_str, &addr) != 1 )
		{
			return -1;
		}
		
		return AF_INET;
	}
	else
	{
		// ipv6
		struct in6_addr addr6 = {{0}};
		
		if( inet_pton(AF_INET6, ip_str, &addr6) != 1 )
		{
			return -1;
		}
		
		return AF_INET6;
	}
	
	return -1;
}

/**
 * @brief ipv6地址的表示方法
 */
void ipv6_addr_representation(const char* ipv6_str)
{
	if(ipv6_str == NULL || ipv6_str[0] == '\0')
	{
		return;
	}
	
	struct in6_addr addr6 = {{0}};
	
	if( inet_pton(AF_INET6, ipv6_str, &addr6) != 1 )
	{
		return;
	}

#if MY_DEBUG
	print_byte_stream((uint8_t*)(&addr6), N_IPV6_BYTES);
	print_binary_stream((uint8_t*)(&addr6), N_IPV6_BYTES);
#endif // MY_DEBUG

	char my_hex[8][8] = {0};
	char colon_expr[64] = {0}; // 冒分十六进制表示法
	char colon_expr2[64] = {0}; // 冒分十六进制表示法（如果存在一组0000，压缩为0）
	char compat_expr[64] = {0}; // 内嵌IPv4地址表示法
	char compat_expr2[64] = {0}; // 内嵌IPv4地址表示法（如果存在一组0000，压缩为0）
	uint8_t* data = addr6.s6_addr;
	
	for(size_t idx = 0; idx < 8; ++idx)
	{
		// 将一组 0000 压缩成 0
		if(data[2 * idx] == 0x00 && data[2 * idx + 1] == 0x00)
		{
			snprintf(my_hex[idx], sizeof(my_hex[idx]), "0");
		}
		else
		{
			snprintf(my_hex[idx], sizeof(my_hex[idx]), "%02x%02x", data[2 * idx], data[2 * idx + 1]);
		}
	}

	// 冒分十六进制表示法
	// XXXX:XXXX:XXXX:XXXX:XXXX:XXXX:XXXX:XXXX
	snprintf(colon_expr, sizeof(colon_expr), "%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x",
	    data[0], data[1], data[2], data[3], data[4], data[5], data[6], data[7], data[8], data[9], data[10], data[11], data[12], data[13], data[14], data[15]);
	
	snprintf(colon_expr2, sizeof(colon_expr2), "%s:%s:%s:%s:%s:%s:%s:%s", my_hex[0], my_hex[1], my_hex[2], my_hex[3], my_hex[4], my_hex[5], my_hex[6], my_hex[7]);
	
	// 内嵌IPv4地址表示法
	// XXXX:XXXX:XXXX:XXXX:XXXX:XXXX:x.x.x.x
	snprintf(compat_expr, sizeof(compat_expr), "%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x:%"PRIu8".%"PRIu8".%"PRIu8".%"PRIu8"",
	    data[0], data[1], data[2], data[3], data[4], data[5], data[6], data[7], data[8], data[9], data[10], data[11],
	    data[12], data[13], data[14], data[15]);

	snprintf(compat_expr2, sizeof(compat_expr2), "%s:%s:%s:%s:%s:%s:%"PRIu8".%"PRIu8".%"PRIu8".%"PRIu8"",
	    my_hex[0], my_hex[1], my_hex[2], my_hex[3], my_hex[4], my_hex[5], data[12], data[13], data[14], data[15]);
	
	printf("%s\n", colon_expr2);
	
	if( strcasecmp(colon_expr, colon_expr2) != 0 )
	{
		printf("%s\n", colon_expr);
	}
	
	printf("%s\n", compat_expr2);
	
	if( strcasecmp(compat_expr, compat_expr2) != 0 )
	{
		printf("%s\n", compat_expr);
	}
}

int main(int argc, char** argv)
{
	if(argc != 2)
	{
		return 0;
	}
	
	// 判断是否是ipv6地址
	if( is_ip_addr(argv[1]) != AF_INET6 )
	{
		return 0;
	}
	
	ipv6_addr_representation(argv[1]);
	
	return 0;
}
