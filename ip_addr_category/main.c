#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <ctype.h>
#include <arpa/inet.h>

#define MY_DEBUG 0

#define N_IPV4_BYTES sizeof(struct in_addr)
#define N_IPV6_BYTES sizeof(struct in6_addr)

typedef enum _ip_addr_category_enum
{
	IP_ERROR,                       // 非法ip地址
	
	IPV4_ADDR_ANY,                  // 0.0.0.0
	IPV4_CLASS_A_RESERVED,          // 0.0.0.1~0.255.255.255
	IPV4_CLASS_A,                   // 1.0.0.0~126.255.255.255
	IPV4_ADDR_LOOPBACK,             // 127.0.0.0~127.255.255.255
	IPV4_CLASS_B,                   // 128.0.0.0~191.255.255.255
	IPV4_CLASS_C,                   // 192.0.0.0~223.255.255.255
	IPV4_CLASS_D,                   // 224.0.0.0~239.255.255.255
	IPV4_CLASS_E,                   // 240.0.0.0~255.255.255.254
	IPV4_ADDR_LIMITED_BROADCAST,    // 255.255.255.255
	IPV4_ADDR_NETWORK_ID,           // ipv4网络地址
	IPV4_ADDR_BROADCAST,            // ipv4直接广播地址
	
	IPV6_ADDR_UNSPECIFIED,          // ::
	IPV6_ADDR_LOOPBACK,             // ::1
	IPV6_ADDR_V4COMPAT,             // ::2~::ffff:ffff
	IPV6_ADDR_V4MAPPED,             // ::ffff:0:0~::ffff:ffff:ffff（::ffff:0:0/96）
	IPV6_ADDR_LINKLOCAL,            // fe80::~febf:ffff:ffff:ffff:ffff:ffff:ffff:ffff（fe80::/10）
	IPV6_ADDR_SITELOCAL,            // fec0::~feff:ffff:ffff:ffff:ffff:ffff:ffff:ffff（fec0::/10）
	IPV6_ADDR_MULTICAST,            // ff00::~ffff:ffff:ffff:ffff:ffff:ffff:ffff:ffff（ff00::/8）
	IPV6_ADDR_UNICAST,              // ipv6单播地址
	//IPV6_ADDR_NETWORK_ID,           // ipv6网络地址
} ip_addr_category_enum_t;

void print_ip_addr_category_enum(ip_addr_category_enum_t category)
{
	switch(category)
	{
	case IP_ERROR:
		printf("IP_ERROR\n");
		break;
	
	case IPV4_ADDR_ANY:
		printf("IPV4_ADDR_ANY\n");
		break;
	case IPV4_CLASS_A_RESERVED:
		printf("IPV4_CLASS_A_RESERVED\n");
		break;
	case IPV4_CLASS_A:
		printf("IPV4_CLASS_A\n");
		break;
	case IPV4_ADDR_LOOPBACK:
		printf("IPV4_ADDR_LOOPBACK\n");
		break;
	case IPV4_CLASS_B:
		printf("IPV4_CLASS_B\n");
		break;
	case IPV4_CLASS_C:
		printf("IPV4_CLASS_C\n");
		break;
	case IPV4_CLASS_D:
		printf("IPV4_CLASS_D\n");
		break;
	case IPV4_CLASS_E:
		printf("IPV4_CLASS_E\n");
		break;
	case IPV4_ADDR_LIMITED_BROADCAST:
		printf("IPV4_ADDR_LIMITED_BROADCAST\n");
		break;
	case IPV4_ADDR_NETWORK_ID:
		printf("IPV4_ADDR_NETWORK_ID\n");
		break;
	case IPV4_ADDR_BROADCAST:
		printf("IPV4_ADDR_BROADCAST\n");
		break;
	
	case IPV6_ADDR_UNSPECIFIED:
		printf("IPV6_ADDR_UNSPECIFIED\n");
		break;
	case IPV6_ADDR_LOOPBACK:
		printf("IPV6_ADDR_LOOPBACK\n");
		break;
	case IPV6_ADDR_V4COMPAT:
		printf("IPV6_ADDR_V4COMPAT\n");
		break;
	case IPV6_ADDR_V4MAPPED:
		printf("IPV6_ADDR_V4MAPPED\n");
		break;
	case IPV6_ADDR_LINKLOCAL:
		printf("IPV6_ADDR_LINKLOCAL\n");
		break;
	case IPV6_ADDR_SITELOCAL:
		printf("IPV6_ADDR_SITELOCAL\n");
		break;
	case IPV6_ADDR_MULTICAST:
		printf("IPV6_ADDR_MULTICAST\n");
		break;
	case IPV6_ADDR_UNICAST:
		printf("IPV6_ADDR_UNICAST\n");
		break;
	//case IPV6_ADDR_NETWORK_ID:
		//printf("IPV6_ADDR_NETWORK_ID\n");
		//break;
	default:
		break;
	}
}

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
 * @brief 判断是否是数值字符串
 *
 * @return int
 * @retval 0 不是
 *         1 是
 */
int is_numeric_str(const char* str)
{
	if(str == NULL || str[0] == '\0')
	{
		return 0;
	}

	size_t idx = 0;
	size_t len = strlen(str);
	
	for(idx = 0; idx < len; ++idx)
	{
		if( isdigit(str[idx]) == 0 )
		{
			return 0;
		}
	}
	
	return 1;
}

/**
 * @brief 判断ip表达式掩码的合法性
 *
 * @return int
 * @retval 0     非法的ip表达式掩码
 *         >0    ip表达式掩码表示的位数
 */
int is_ip_mask(int ip_family, const char* mask_str)
{
	if(ip_family != AF_INET && ip_family != AF_INET6)
	{
		return 0;
	}
	
	if(mask_str == NULL || mask_str[0] == '\0')
	{
		return 0;
	}
	
	if( strchr(mask_str, ':') == NULL )
	{
		// ipv4
		struct in_addr addr = {0};
		
		if( inet_pton(AF_INET, mask_str, &addr) != 1 )
		{
			return 0;
		}
		
		if(ip_family == AF_INET6)
		{
			return 0;
		}
		
		uint32_t mask = 0xffffffff;
		uint32_t s_addr = ntohl(addr.s_addr);
		
		for(int idx = 1; idx <= 32; ++idx)
		{
			if( s_addr == (mask << (32 - idx)) )
			{
				return idx;
			}
		}
		
		return 0;
	}
	else
	{
/*
		// ipv6
		struct in6_addr addr6 = {{0}};
		
		if( inet_pton(AF_INET6, mask_str, &addr6) != 1 )
		{
			return 0;
		}
		
		if(ip_family == AF_INET)
		{
			return 0;
		}
		
		uint8_t mask[N_IPV6_BYTES] = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff};
		
		for(int idx = 128; idx >= 1; --idx)
		{
			if( memcmp(&addr6, mask, N_IPV6_BYTES) == 0 )
			{
				return idx;
			}
			
			int byte_idx = (idx / 8);
			int remain_bits = (idx % 8);
			
			if(byte_idx > 0 && remain_bits == 0)
			{
				--byte_idx;
			}
			
			mask[byte_idx] <<= 1;
		}
*/
		return 0;
	}
	
	return 0;
}

/**
 * @brief 判断ip数值掩码的合法性
 *
 * @return int
 * @retval 0 不合法
 *         1 合法
 */
int is_numeric_mask(int family, const char* mask_str)
{
	if(family != AF_INET && family != AF_INET6)
	{
		return 0;
	}
	
	if(mask_str == NULL || mask_str[0] == '\0')
	{
		return 0;
	}
	
	if( is_numeric_str(mask_str) == 0 )
	{
		return 0;
	}
	
	int mask_len = atoi(mask_str);
	
	if( family == AF_INET && (mask_len < 1 || mask_len > 32) )
	{
		return 0;
	}
	
	if( family == AF_INET6 && (mask_len < 1 || mask_len > 128) )
	{
		return 0;
	}
	
	return 1;
}

/**
 * @brief 根据掩码位数判断是否是ipv4网络地址
 *
 * @return int
 * @retval 0 不是
 *         1 是
 */
int is_ipv4_network_addr(struct in_addr addr, int mask_len)
{
	if(mask_len <= 0)
	{
		return 0;
	}
	
	int mask_bytes = (mask_len / 8);
	int mask_remain_bits = (mask_len % 8);
	uint8_t network_addr[N_IPV4_BYTES] = {0};
	
	memcpy(network_addr, &addr, N_IPV4_BYTES);
	
	// 计算网络地址
	if( (mask_bytes == 0 && mask_remain_bits != 0) || (mask_bytes != 0 && mask_remain_bits != 0) )
	{
		network_addr[ mask_bytes ] &= (uint8_t)(0xFF << (8 - mask_remain_bits));
		memset(network_addr + mask_bytes + 1, 0, sizeof(network_addr) - mask_bytes - 1);
	}
	else if(mask_bytes != 0 && mask_remain_bits == 0)
	{
		memset(network_addr + mask_bytes, 0, sizeof(network_addr) - mask_bytes);
	}
	
	if( memcmp(&addr, network_addr, N_IPV4_BYTES) == 0 )
	{
		return 1;
	}
	
	return 0;
}

/**
 * @brief 根据掩码位数判断是否是ipv4广播地址
 *
 * @return int
 * @retval 0 不是
 *         1 是
 */
int is_ipv4_broadcast_addr(struct in_addr addr, int mask_len)
{
	if(mask_len <= 0)
	{
		return 0;
	}
	
	int mask_bytes = (mask_len / 8);
	int mask_remain_bits = (mask_len % 8);
	uint8_t broadcast_addr[N_IPV4_BYTES] = {0};
	
	memcpy(broadcast_addr, &addr, N_IPV4_BYTES);
	
	// 计算广播地址
	if( (mask_bytes == 0 && mask_remain_bits != 0) || (mask_bytes != 0 && mask_remain_bits != 0) )
	{
		broadcast_addr[ mask_bytes ] |= (uint8_t)(0xFF >> (mask_remain_bits));
		memset(broadcast_addr + mask_bytes + 1, 0xFF, sizeof(broadcast_addr) - mask_bytes - 1);
	}
	else if(mask_bytes != 0 && mask_remain_bits == 0)
	{
		memset(broadcast_addr + mask_bytes, 0xFF, sizeof(broadcast_addr) - mask_bytes);
	}
	
	if( memcmp(&addr, broadcast_addr, N_IPV4_BYTES) == 0 )
	{
		return 1;
	}
	
	return 0;
}

/**
 * @brief 判断ipv4地址类别
 */
ip_addr_category_enum_t ipv4_addr_category(unsigned long s_addr)
{
	if( IN_CLASSA(s_addr) )
	{
		return IPV4_CLASS_A;
	}
	
	if( IN_CLASSB(s_addr) )
	{
		return IPV4_CLASS_B;
	}
	
	if( IN_CLASSC(s_addr) )
	{
		return IPV4_CLASS_C;
	}
	
	if( IN_CLASSD(s_addr) )
	{
		return IPV4_CLASS_D;
	}
	
	return IPV4_CLASS_E;
}

/**
 * @brief 更详细的判断ipv4地址类别
 */
ip_addr_category_enum_t ipv4_addr_category_check(const char* ip_str, int mask_len)
{
	if(ip_str == NULL || ip_str[0] == '\0')
	{
		return IP_ERROR;
	}
	
	struct in_addr addr = {0};

	if( inet_pton(AF_INET, ip_str, &addr) != 1 )
	{
		return IP_ERROR;
	}

#if MY_DEBUG
	print_byte_stream((uint8_t*)(&addr), N_IPV4_BYTES);
	print_binary_stream((uint8_t*)(&addr), N_IPV4_BYTES);
#endif // MY_DEBUG
	
	uint32_t s_addr = ntohl(addr.s_addr);
	ip_addr_category_enum_t category = ipv4_addr_category(s_addr);
	
	switch(category)
	{
	case IPV4_CLASS_A:
	{
		// 0.0.0.0
		if( addr.s_addr == INADDR_ANY )
		{
			return IPV4_ADDR_ANY;
		}
		
		// 0.0.0.1~0.255.255.255
		if( 0x00000001 <= s_addr && s_addr <= 0x00ffffff )
		{
			return IPV4_CLASS_A_RESERVED;
		}
		
		// 127.0.0.0~127.255.255.255
		//if( (s_addr & 0x7f000000) == 0x7f000000 )
		if( 0x7f000000 <= s_addr && s_addr <= 0x7fffffff )
		{
			return IPV4_ADDR_LOOPBACK;
		}
/*
		// A类地址，默认掩码8位
		if(mask_len == 0)
		{
			mask_len = 8;
		}
*/
		if( is_ipv4_network_addr(addr, mask_len) == 1 )
		{
			return IPV4_ADDR_NETWORK_ID;
		}
	
		if( is_ipv4_broadcast_addr(addr, mask_len) == 1 )
		{
			return IPV4_ADDR_BROADCAST;
		}
		
		return category;
	}
	case IPV4_CLASS_B:
	{
/*
		// B类地址，默认掩码16位
		if(mask_len == 0)
		{
			mask_len = 16;
		}
*/
		if( is_ipv4_network_addr(addr, mask_len) == 1 )
		{
			return IPV4_ADDR_NETWORK_ID;
		}
	
		if( is_ipv4_broadcast_addr(addr, mask_len) == 1 )
		{
			return IPV4_ADDR_BROADCAST;
		}
		
		return category;
	}
	case IPV4_CLASS_C:
	{
/*
		// C类地址，默认掩码24位
		if(mask_len == 0)
		{
			mask_len = 24;
		}
*/
		if( is_ipv4_network_addr(addr, mask_len) == 1 )
		{
			return IPV4_ADDR_NETWORK_ID;
		}
	
		if( is_ipv4_broadcast_addr(addr, mask_len) == 1 )
		{
			return IPV4_ADDR_BROADCAST;
		}
		
		return category;
	}
	case IPV4_CLASS_D:
	{
		return category;
	}
	case IPV4_CLASS_E:
	{
		// 255.255.255.255
		if( addr.s_addr == INADDR_BROADCAST )
		{
			return IPV4_ADDR_LIMITED_BROADCAST;
		}
		
		return category;
	}
	default:
		return IP_ERROR;
	}
	
	return IP_ERROR;
}

/**
 * @brief 根据前缀长度判断是否是ipv6网络地址
 *
 * @return int
 * @retval 0 不是
 *         1 是
 */
int is_ipv6_network_addr(struct in6_addr addr6, int prefix_len)
{
	if(prefix_len <= 0)
	{
		return 0;
	}
	
	int prefix_bytes = (prefix_len / 8);
	int prefix_remain_bits = (prefix_len % 8);
	uint8_t network_addr6[N_IPV6_BYTES] = {0};
	
	memcpy(network_addr6, &addr6, N_IPV6_BYTES);
	
	// 计算网络地址
	if( (prefix_bytes == 0 && prefix_remain_bits != 0) || (prefix_bytes != 0 && prefix_remain_bits != 0) )
	{
		network_addr6[ prefix_bytes ] &= (uint8_t)(0xFF << (8 - prefix_remain_bits));
		memset(network_addr6 + prefix_bytes + 1, 0, sizeof(network_addr6) - prefix_bytes - 1);
	}
	else if(prefix_bytes != 0 && prefix_remain_bits == 0)
	{
		memset(network_addr6 + prefix_bytes, 0, sizeof(network_addr6) - prefix_bytes);
	}
	
	if( memcmp(&addr6, network_addr6, N_IPV6_BYTES) == 0 )
	{
		return 1;
	}
	
	return 0;
}

/**
 * @brief 判断ipv6地址类别
 */
ip_addr_category_enum_t ipv6_addr_category_check(const char* ip_str, int prefix_len)
{
	if(ip_str == NULL || ip_str[0] == '\0')
	{
		return IP_ERROR;
	}
	
	struct in6_addr addr6 = {{0}};
	
	if( inet_pton(AF_INET6, ip_str, &addr6) != 1 )
	{
		return IP_ERROR;
	}

#if MY_DEBUG
	print_byte_stream((uint8_t*)(&addr6), N_IPV6_BYTES);
	print_binary_stream((uint8_t*)(&addr6), N_IPV6_BYTES);
#endif // MY_DEBUG

	// ::
	if( IN6_IS_ADDR_UNSPECIFIED(&addr6) )
	{
		return IPV6_ADDR_UNSPECIFIED;
	}
	
	// ::1
	if( IN6_IS_ADDR_LOOPBACK(&addr6) )
	{
		return IPV6_ADDR_LOOPBACK;
	}
	
	// ::2~::ffff:ffff
	if( IN6_IS_ADDR_V4COMPAT(&addr6) )
	{
		return IPV6_ADDR_V4COMPAT;
	}
	
	// ::ffff:0:0/96
	if( IN6_IS_ADDR_V4MAPPED(&addr6) )
	{
		return IPV6_ADDR_V4MAPPED;
	}
	
	// fe80::/10
	if( IN6_IS_ADDR_LINKLOCAL(&addr6) )
	{
		return IPV6_ADDR_LINKLOCAL;
	}
	
	// fec0::/10
	if( IN6_IS_ADDR_SITELOCAL(&addr6) )
	{
		return IPV6_ADDR_SITELOCAL;
	}
/*
	printf("%d\n", IN6_IS_ADDR_MC_NODELOCAL(&addr6));
	printf("%d\n", IN6_IS_ADDR_MC_LINKLOCAL(&addr6));
	printf("%d\n", IN6_IS_ADDR_MC_SITELOCAL(&addr6));
	printf("%d\n", IN6_IS_ADDR_MC_ORGLOCAL(&addr6));
	printf("%d\n", IN6_IS_ADDR_MC_GLOBAL(&addr6));
*/
	// ff00::/8
	if( IN6_IS_ADDR_MULTICAST(&addr6) )
	{
		return IPV6_ADDR_MULTICAST;
	}
/*
	if( is_ipv6_network_addr(addr6, prefix_len) == 1 )
	{
		return IPV6_ADDR_NETWORK_ID;
	}
*/
	return IPV6_ADDR_UNICAST;
}

/**
 * @brief 判断ip地址类别
 */
ip_addr_category_enum_t ip_addr_category_check(const char* ip_str, int mask_len)
{
	if(ip_str == NULL || ip_str[0] == '\0')
	{
		return IP_ERROR;
	}
	
	if( strchr(ip_str, ':') == NULL )
	{
		// ipv4
		return ipv4_addr_category_check(ip_str, mask_len);
	}
	else
	{
		// ipv6
		return ipv6_addr_category_check(ip_str, mask_len);
	}
	
	return IP_ERROR;
}

int main(int argc, char** argv)
{
	if(argc != 2 && argc != 3)
	{
		return 0;
	}
	
	int ip_family = is_ip_addr(argv[1]);
	
	// 判断ip地址的合法性
	if(ip_family == -1)
	{
		print_ip_addr_category_enum(IP_ERROR);
		return 0;
	}
	
	int mask_len = 0;
	
	do
	{
		if(argc == 2)
		{
			break;
		}
		
		int len = is_ip_mask(ip_family, argv[2]);
		
		if(len > 0)
		{
			mask_len = len;
			break;
		}
		
		if( is_numeric_mask(ip_family, argv[2]) == 1 )
		{
			mask_len = atoi(argv[2]);
			break;
		}
		
		printf("IP_MASK_ERROR\n");
		return 0;
	}
	while(0);
	
	// 判断ip地址类别
	print_ip_addr_category_enum( ip_addr_category_check(argv[1], mask_len) );
	
	return 0;
}
