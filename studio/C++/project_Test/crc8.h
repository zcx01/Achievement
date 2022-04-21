#ifndef __UTILITIES_CRC8_H__
#define __UTILITIES_CRC8_H__

#include <stdint.h>
#include <stdbool.h>
#ifdef __cplusplus
extern "C" {
#endif
//=================================================================================//
extern uint8_t UTILITY_CRC8_Calculate(uint8_t init_value, const uint8_t data[], uint32_t data_length, bool is_init_enable);
extern uint8_t UTILITY_CRC8_Calculate_x84321(uint8_t init_value,const uint8_t *data, uint32_t data_length, bool is_init_enable, bool post_event);
//=================================================================================//
#ifdef __cplusplus
}
#endif
#endif /* __UTILITIES_CRC8_H__ */

