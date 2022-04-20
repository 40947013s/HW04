#pragma once

#include <stdint.h>

typedef struct _sTest
{
    uint8_t version;
    uint8_t ihl;
    uint8_t typeofservice;
    uint16_t totallength;
    uint16_t identification;
    uint8_t flags;
    uint16_t fragmentoffset;
    uint8_t timetolive;
    uint8_t protocol;
    uint16_t headerchecksum;
    uint32_t sourceaddress;
    uint32_t destinationaddress;
    uint8_t options[3];
    uint8_t padding;
}Test;

Test * test_init( void );
void test_free( Test * );
int test_encode( void *, const Test * );
int test_decode( const void *, Test * );
