/*
  C-file generated by �C/BmpCvt V2.30b, compiled May  8 2002, 10:05:37

  (c) 2002  Micrium, Inc.
  www.micrium.com

  (c) 1998-2002  Segger
  Microcontroller Systeme GmbH
  www.segger.com

  Source file: MicriumLogo
  Dimensions:  145 * 39
  NumColors:   183
*/

#include "stdlib.h"

#include "GUI.H"

/*   Palette
The following are the entries of the palette table.
Every entry is a 32-bit value (of which 24 bits are actually used)
the lower   8 bits represent the Red component,
the middle  8 bits represent the Green component,
the highest 8 bits (of the 24 bits used) represent the Blue component
as follows:   0xBBGGRR
*/

const GUI_COLOR ColorsMicriumLogo[] = {
     0xFF0000,0xFF0043,0xFF003D,0xDE1D6C
    ,0xB63A94,0xBB378F,0xB33D98,0xFF003B
    ,0xA04CAD,0x2B98FF,0x3890FF,0xA945A2
    ,0xFF002F,0x1EA0FF,0xA648A6,0x3B8FFF
    ,0x4887FF,0x4687FF,0x3393FF,0xFF0030
    ,0x2F97FF,0x2C97FF,0xFF0023,0xA14AAA
    ,0x3294FF,0x3E8CFF,0x259CFF,0x3990FF
    ,0xAE429E,0xFF003C,0xFF003F,0xC23288
    ,0x7C65CE,0x835FC7,0xFF003E,0xFF0037
    ,0x746AD5,0x4489FF,0xFF0035,0xFF0022
    ,0xEE0F5A,0xC62F84,0xCA2C80,0xC33287
    ,0xFF002A,0xFF0039,0xFF0044,0xFF0033
    ,0xFF0048,0x6A70DF,0x4588FF,0x3B8EFF
    ,0xFF0031,0x4E83F9,0x587CEF,0xD12779
    ,0x4887FE,0x3592FF,0x3791FF,0x3394FF
    ,0x567EF1,0x9057BB,0xF50953,0xB23E9A
    ,0x4C84FA,0x428AFF,0x855EC5,0xFF0024
    ,0xFA044D,0x4A86FC,0x8E58BD,0x5082F7
    ,0xC1338A,0x2C98FF,0xA449A8,0x3691FF
    ,0x4389FF,0xF00D57,0x9751B4,0x3A8FFF
    ,0x3C8DFF,0xD62373,0x2A99FF,0xC23389
    ,0x408BFF,0x865EC5,0xFF001E,0x2E97FF
    ,0x279BFF,0xBC378F,0xD92071,0xB53C97
    ,0xF9064F,0xFF002C,0x8062CB,0x3493FF
    ,0x209FFF,0xFF0045,0x587DF0,0x438AFF
    ,0xFF002B,0x4F82F8,0x3D8DFF,0xFF002E
    ,0xFF0009,0xAD43A0,0xA14BAB,0xC0348B
    ,0x3096FF,0x7B65CF,0x7767D3,0x557FF3
    ,0xFF0027,0x4A86FD,0xFF0018,0x4B85FB
    ,0xFF0020,0x8B5AC0,0xAD429F,0xFF0029
    ,0x229EFF,0xB03F9C,0x3195FF,0xEF0E58
    ,0xA349A8,0x9E4DAE,0xAB44A1,0xFF0006
    ,0xFD0049,0x2F96FF,0x4987FD,0xFF0025
    ,0x6574E3,0x6872E1,0xA845A2,0xE71561
    ,0xDF1C6A,0x9156BA,0xFF0042,0x9E4DAF
    ,0xAF429E,0xA14CAC,0xA846A3,0xE21966
    ,0xFF0036,0x3692FF,0x4F83F9,0xCB2B80
    ,0x239EFF,0x7E63CC,0x7768D3,0x5E78EA
    ,0xFF0026,0xB73A94,0xFF0034,0xFF0038
    ,0x4F83F8,0x3F8BFF,0x7868D3,0xF8064F
    ,0xBB3891,0x8161C9,0x597CEF,0x3F8CFF
    ,0x289AFF,0x8C59BE,0x4688FF,0xA449A7
    ,0x2B99FF,0xF8074F,0x895BC2,0xFF0032
    ,0xFF0028,0xC72E83,0x9553B6,0xC82E84
    ,0xEA135E,0xBD368D,0xC13389,0xF50952
    ,0xB83991,0xA548A6,0x398FFF
};

const GUI_LOGPALETTE PalMicriumLogo = {
  183,	/* number of entries */
  0, 	/* No transparency */
  &ColorsMicriumLogo[0]
};

const unsigned char acMicriumLogo[] = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x01, 0x00, 0x00, 0x00, 0x01, 0x02, 0x02, 0x02, 0x02, 0x02, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x03, 0x04, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x04, 0x03, 0x01, 0x00, 0x00, 0x00, 0x01, 0x03, 0x04, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x04, 0x03, 0x01, 0x00, 0x01, 0x03, 0x04, 0x05, 0x05, 0x05, 0x04, 0x03, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x06, 0x05, 0x05, 0x05, 0x05, 0x06, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x08, 0x09, 0x0A, 0x0A, 0x0A, 0x0A, 0x0A, 0x0A, 0x09, 0x0B, 0x07, 0x00, 0x00, 0x00, 0x07, 0x0B, 0x09, 0x0A, 0x0A, 0x0A, 0x0A, 0x0A, 0x0A, 0x09, 0x08, 0x07, 0x00, 0x07, 0x08, 0x09, 0x0A, 0x0A, 0x0A, 0x09, 0x08, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0C, 0x0D, 0x0A, 0x0A, 0x0A, 0x0A, 0x0D, 0x0C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x0E, 0x0F, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x11, 0x12, 0x13, 0x00, 0x00, 0x00, 0x13, 0x12, 0x11, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x0F, 0x0E, 0x07, 0x00, 0x07, 0x0E, 0x0F, 0x10, 0x10, 0x10, 0x0F, 0x0E, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0C, 0x14, 0x10, 0x10, 0x10, 0x10, 0x14, 0x0C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x0E, 0x0F, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x15, 0x16, 0x00, 0x00, 0x00, 0x16, 0x15, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x0F, 0x0E, 0x07, 0x00, 0x07, 0x17, 0x18, 0x19, 0x19, 0x19, 0x18, 0x17, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0C, 0x1A, 0x19, 0x19, 0x19, 0x19, 0x1A, 0x0C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x0E, 0x0F, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x1B, 0x1C, 0x1D, 0x00, 0x1D, 0x1C, 0x1B, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x0F, 0x0E, 0x07, 0x00, 0x1E, 0x1F, 0x20, 0x21, 0x21, 0x21, 0x20, 0x1F, 0x1E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x22, 0x22, 0x22, 0x22, 0x22, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x22, 0x22, 0x01, 0x00, 0x23, 0x24, 0x21, 0x21, 0x21, 0x21, 0x24, 0x23, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x22, 0x22, 0x22, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x22, 0x22, 0x22, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x0E, 0x0F, 0x10, 0x10, 0x10, 0x10, 0x25, 0x10, 0x10, 0x0F, 0x1C, 0x07, 0x00, 0x07, 0x1C, 0x0F, 0x10, 0x10, 0x25, 0x10, 0x10, 0x10, 0x10, 0x0F, 0x0E, 0x07, 0x00, 0x00, 0x26, 0x27, 0x27, 0x27, 0x27, 0x27, 0x26, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1E, 0x0C, 0x28, 0x29, 0x2A, 0x2A, 0x2A, 0x2B, 0x2C, 0x2D, 0x2E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x2F, 0x2F, 0x2F, 0x2F, 0x2F, 0x02, 0x2E, 0x2C, 0x2B, 0x29, 0x28, 0x26, 0x30, 0x27, 0x27, 0x27, 0x27, 0x27, 0x27, 0x00, 0x00, 0x00, 0x02, 0x2F, 0x2F, 0x2F, 0x2F, 0x2F, 0x02, 0x00, 0x00, 0x00, 0x02, 0x2F, 0x2F, 0x2F, 0x2F, 0x2F, 0x02, 0x00, 0x00, 0x00, 0x02, 0x2F, 0x2F, 0x2F, 0x2F, 0x2F, 0x00, 0x2E, 0x0C, 0x28, 0x29, 0x2A, 0x29, 0x28, 0x26, 0x00, 0x00, 0x2E, 0x0C, 0x28, 0x29, 0x2A, 0x2B, 0x2C, 0x1E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x0E, 0x0F, 0x10, 0x10, 0x10, 0x25, 0x31, 0x25, 0x10, 0x32, 0x33, 0x34, 0x00, 0x34, 0x33, 0x32, 0x10, 0x25, 0x31, 0x25, 0x10, 0x10, 0x10, 0x0F, 0x0E, 0x07, 0x00, 0x02, 0x1C, 0x35, 0x36, 0x36, 0x36, 0x35, 0x1C, 0x02, 0x00, 0x00, 0x00, 0x2E, 0x34, 0x37, 0x35, 0x38, 0x39, 0x3A, 0x3A, 0x3A, 0x3B, 0x3C, 0x3D, 0x3E, 0x07, 0x00, 0x00, 0x00, 0x00, 0x2F, 0x25, 0x36, 0x36, 0x36, 0x35, 0x3F, 0x01, 0x40, 0x3B, 0x39, 0x41, 0x42, 0x43, 0x25, 0x36, 0x36, 0x36, 0x36, 0x25, 0x2F, 0x00, 0x02, 0x1C, 0x35, 0x36, 0x36, 0x36, 0x35, 0x1C, 0x02, 0x00, 0x02, 0x1C, 0x35, 0x36, 0x36, 0x36, 0x35, 0x1C, 0x02, 0x00, 0x02, 0x1C, 0x35, 0x36, 0x36, 0x36, 0x25, 0x2C, 0x44, 0x45, 0x38, 0x39, 0x3A, 0x39, 0x41, 0x46, 0x2C, 0x1E, 0x44, 0x45, 0x38, 0x39, 0x3A, 0x3B, 0x47, 0x37, 0x26, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x0E, 0x0F, 0x10, 0x10, 0x10, 0x0F, 0x48, 0x0F, 0x10, 0x10, 0x49, 0x43, 0x00, 0x2C, 0x49, 0x10, 0x10, 0x0F, 0x48, 0x0F, 0x10, 0x10, 0x10, 0x0F, 0x0E, 0x07, 0x00, 0x07, 0x4A, 0x4B, 0x4C, 0x4C, 0x4C, 0x4B, 0x4A, 0x07, 0x00, 0x00, 0x2E, 0x4D, 0x4E, 0x09, 0x4C, 0x32, 0x10, 0x10, 0x10, 0x10, 0x10, 0x4C, 0x4F, 0x50, 0x51, 0x07, 0x00, 0x00, 0x00, 0x0C, 0x52, 0x4C, 0x4C, 0x4C, 0x4B, 0x53, 0x41, 0x54, 0x10, 0x10, 0x33, 0x55, 0x56, 0x52, 0x4C, 0x4C, 0x4C, 0x4C, 0x52, 0x0C, 0x00, 0x07, 0x4A, 0x4B, 0x4C, 0x4C, 0x4C, 0x4B, 0x4A, 0x07, 0x00, 0x07, 0x4A, 0x4B, 0x4C, 0x4C, 0x4C, 0x4B, 0x4A, 0x07, 0x00, 0x07, 0x4A, 0x4B, 0x4C, 0x4C, 0x4C, 0x57, 0x13, 0x0A, 0x54, 0x32, 0x10, 0x10, 0x10, 0x32, 0x18, 0x4E, 0x07, 0x0A, 0x54, 0x32, 0x10, 0x10, 0x10, 0x4C, 0x58, 0x59, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x0E, 0x0F, 0x10, 0x10, 0x10, 0x3A, 0x5A, 0x3A, 0x10, 0x10, 0x0A, 0x5B, 0x2D, 0x5C, 0x18, 0x10, 0x10, 0x3A, 0x5A, 0x3A, 0x10, 0x10, 0x10, 0x0F, 0x0E, 0x07, 0x00, 0x07, 0x0E, 0x0F, 0x10, 0x10, 0x10, 0x0F, 0x0E, 0x07, 0x00, 0x00, 0x5D, 0x5E, 0x5F, 0x10, 0x10, 0x10, 0x10, 0x54, 0x54, 0x25, 0x10, 0x10, 0x10, 0x32, 0x60, 0x61, 0x2E, 0x00, 0x00, 0x0C, 0x14, 0x10, 0x10, 0x10, 0x32, 0x62, 0x63, 0x10, 0x10, 0x10, 0x57, 0x02, 0x64, 0x14, 0x10, 0x10, 0x10, 0x10, 0x14, 0x0C, 0x00, 0x07, 0x0E, 0x0F, 0x10, 0x10, 0x10, 0x0F, 0x0E, 0x07, 0x00, 0x07, 0x0E, 0x0F, 0x10, 0x10, 0x10, 0x0F, 0x0E, 0x07, 0x00, 0x07, 0x0E, 0x0F, 0x10, 0x10, 0x10, 0x32, 0x65, 0x63, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x4F, 0x65, 0x63, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x32, 0x66, 0x67, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x0E, 0x0F, 0x10, 0x10, 0x10, 0x14, 0x68, 0x52, 0x10, 0x10, 0x0F, 0x69, 0x0C, 0x6A, 0x0F, 0x10, 0x10, 0x52, 0x68, 0x14, 0x10, 0x10, 0x10, 0x0F, 0x0E, 0x07, 0x00, 0x07, 0x0E, 0x0F, 0x10, 0x10, 0x10, 0x0F, 0x0E, 0x07, 0x00, 0x02, 0x6B, 0x6C, 0x10, 0x10, 0x10, 0x10, 0x12, 0x6D, 0x6E, 0x6F, 0x54, 0x10, 0x10, 0x10, 0x32, 0x0A, 0x70, 0x00, 0x00, 0x0C, 0x14, 0x10, 0x10, 0x10, 0x10, 0x32, 0x10, 0x4F, 0x5F, 0x4B, 0x71, 0x13, 0x0C, 0x14, 0x10, 0x10, 0x10, 0x10, 0x14, 0x0C, 0x00, 0x07, 0x0E, 0x0F, 0x10, 0x10, 0x10, 0x0F, 0x0E, 0x07, 0x00, 0x07, 0x0E, 0x0F, 0x10, 0x10, 0x10, 0x0F, 0x0E, 0x07, 0x00, 0x07, 0x0E, 0x0F, 0x10, 0x10, 0x10, 0x10, 0x32, 0x4F, 0x5F, 0x4F, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x32, 0x4F, 0x5F, 0x4F, 0x10, 0x10, 0x10, 0x10, 0x10, 0x6C, 0x44, 0x2E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x0E, 0x0F, 0x10, 0x10, 0x10, 0x14, 0x72, 0x73, 0x25, 0x10, 0x32, 0x4C, 0x74, 0x75, 0x19, 0x10, 0x25, 0x73, 0x72, 0x14, 0x10, 0x10, 0x10, 0x0F, 0x0E, 0x07, 0x00, 0x07, 0x0E, 0x0F, 0x10, 0x10, 0x10, 0x0F, 0x0E, 0x07, 0x00, 0x67, 0x54, 0x32, 0x10, 0x10, 0x10, 0x3A, 0x76, 0x77, 0x2F, 0x02, 0x45, 0x66, 0x54, 0x4F, 0x5F, 0x78, 0x79, 0x02, 0x00, 0x0C, 0x14, 0x10, 0x10, 0x10, 0x10, 0x10, 0x7A, 0x3F, 0x7B, 0x7C, 0x59, 0x22, 0x0C, 0x14, 0x10, 0x10, 0x10, 0x10, 0x14, 0x0C, 0x00, 0x07, 0x0E, 0x0F, 0x10, 0x10, 0x10, 0x0F, 0x0E, 0x07, 0x00, 0x07, 0x0E, 0x0F, 0x10, 0x10, 0x10, 0x0F, 0x0E, 0x07, 0x00, 0x07, 0x0E, 0x0F, 0x10, 0x10, 0x10, 0x10, 0x3A, 0x3F, 0x7B, 0x3F, 0x7A, 0x10, 0x10, 0x10, 0x10, 0x10, 0x3A, 0x3F, 0x7B, 0x3F, 0x7A, 0x10, 0x10, 0x10, 0x10, 0x0F, 0x7D, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x0E, 0x0F, 0x10, 0x10, 0x10, 0x14, 0x27, 0x7E, 0x0F, 0x10, 0x10, 0x09, 0x7F, 0x1A, 0x10, 0x10, 0x0F, 0x7E, 0x27, 0x14, 0x10, 0x10, 0x10, 0x0F, 0x0E, 0x07, 0x00, 0x07, 0x0E, 0x0F, 0x10, 0x10, 0x10, 0x0F, 0x0E, 0x07, 0x2E, 0x80, 0x81, 0x10, 0x10, 0x10, 0x25, 0x82, 0x83, 0x00, 0x00, 0x07, 0x6B, 0x84, 0x85, 0x86, 0x87, 0x88, 0x28, 0x61, 0x00, 0x0C, 0x14, 0x10, 0x10, 0x10, 0x10, 0x66, 0x89, 0x64, 0x8A, 0x07, 0x22, 0x00, 0x0C, 0x14, 0x10, 0x10, 0x10, 0x10, 0x14, 0x0C, 0x00, 0x07, 0x0E, 0x0F, 0x10, 0x10, 0x10, 0x0F, 0x0E, 0x07, 0x00, 0x07, 0x0E, 0x0F, 0x10, 0x10, 0x10, 0x0F, 0x0E, 0x07, 0x00, 0x07, 0x0E, 0x0F, 0x10, 0x10, 0x10, 0x25, 0x82, 0x83, 0x8A, 0x64, 0x89, 0x66, 0x10, 0x10, 0x10, 0x25, 0x82, 0x83, 0x8A, 0x64, 0x89, 0x66, 0x10, 0x10, 0x10, 0x0F, 0x0E, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x0E, 0x0F, 0x10, 0x10, 0x10, 0x14, 0x83, 0x59, 0x0A, 0x10, 0x10, 0x33, 0x59, 0x33, 0x10, 0x10, 0x0A, 0x59, 0x83, 0x14, 0x10, 0x10, 0x10, 0x0F, 0x0E, 0x07, 0x00, 0x07, 0x0E, 0x0F, 0x10, 0x10, 0x10, 0x0F, 0x0E, 0x07, 0x07, 0x8B, 0x0F, 0x10, 0x10, 0x10, 0x0F, 0x8C, 0x07, 0x00, 0x00, 0x00, 0x22, 0x26, 0x26, 0x07, 0x8A, 0x8A, 0x61, 0x00, 0x00, 0x0C, 0x14, 0x10, 0x10, 0x10, 0x10, 0x0F, 0x8D, 0x07, 0x00, 0x00, 0x00, 0x00, 0x0C, 0x14, 0x10, 0x10, 0x10, 0x10, 0x14, 0x0C, 0x00, 0x07, 0x0E, 0x0F, 0x10, 0x10, 0x10, 0x0F, 0x0E, 0x07, 0x00, 0x07, 0x0E, 0x0F, 0x10, 0x10, 0x10, 0x0F, 0x0E, 0x07, 0x00, 0x07, 0x0E, 0x0F, 0x10, 0x10, 0x10, 0x0F, 0x8C, 0x07, 0x00, 0x07, 0x8E, 0x0F, 0x10, 0x10, 0x10, 0x0F, 0x8C, 0x07, 0x00, 0x07, 0x8E, 0x0F, 0x10, 0x10, 0x10, 0x0F, 0x0E, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x0E, 0x0F, 0x10, 0x10, 0x10, 0x14, 0x0C, 0x83, 0x09, 0x10, 0x10, 0x10, 0x33, 0x10, 0x10, 0x10, 0x09, 0x83, 0x0C, 0x14, 0x10, 0x10, 0x10, 0x0F, 0x0E, 0x07, 0x00, 0x07, 0x0E, 0x0F, 0x10, 0x10, 0x10, 0x0F, 0x0E, 0x07, 0x07, 0x0E, 0x0F, 0x10, 0x10, 0x10, 0x0F, 0x0E, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0C, 0x14, 0x10, 0x10, 0x10, 0x10, 0x18, 0x80, 0x2E, 0x00, 0x00, 0x00, 0x00, 0x0C, 0x14, 0x10, 0x10, 0x10, 0x10, 0x14, 0x0C, 0x00, 0x07, 0x0E, 0x0F, 0x10, 0x10, 0x10, 0x0F, 0x0E, 0x07, 0x00, 0x07, 0x0E, 0x0F, 0x10, 0x10, 0x10, 0x0F, 0x0E, 0x07, 0x00, 0x07, 0x0E, 0x0F, 0x10, 0x10, 0x10, 0x0F, 0x0E, 0x07, 0x00, 0x07, 0x0E, 0x0F, 0x10, 0x10, 0x10, 0x0F, 0x0E, 0x07, 0x00, 0x07, 0x0E, 0x0F, 0x10, 0x10, 0x10, 0x0F, 0x0E, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x0E, 0x0F, 0x10, 0x10, 0x10, 0x14, 0x0C, 0x34, 0x4C, 0x32, 0x10, 0x10, 0x10, 0x10, 0x10, 0x32, 0x4C, 0x34, 0x0C, 0x14, 0x10, 0x10, 0x10, 0x0F, 0x0E, 0x07, 0x00, 0x07, 0x0E, 0x0F, 0x10, 0x10, 0x10, 0x0F, 0x0E, 0x07, 0x07, 0x0E, 0x0F, 0x10, 0x10, 0x10, 0x0F, 0x0E, 0x07, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0C, 0x14, 0x10, 0x10, 0x10, 0x10, 0x14, 0x64, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0C, 0x14, 0x10, 0x10, 0x10, 0x10, 0x14, 0x0C, 0x00, 0x07, 0x0E, 0x0F, 0x10, 0x10, 0x10, 0x0F, 0x0E, 0x07, 0x00, 0x07, 0x0E, 0x0F, 0x10, 0x10, 0x10, 0x0F, 0x0E, 0x07, 0x00, 0x07, 0x0E, 0x0F, 0x10, 0x10, 0x10, 0x0F, 0x0E, 0x07, 0x00, 0x07, 0x0E, 0x0F, 0x10, 0x10, 0x10, 0x0F, 0x0E, 0x07, 0x00, 0x07, 0x0E, 0x0F, 0x10, 0x10, 0x10, 0x0F, 0x0E, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x0E, 0x0F, 0x10, 0x10, 0x10, 0x14, 0x0C, 0x07, 0x69, 0x0F, 0x10, 0x10, 0x10, 0x10, 0x10, 0x0F, 0x69, 0x07, 0x0C, 0x14, 0x10, 0x10, 0x10, 0x0F, 0x0E, 0x07, 0x00, 0x07, 0x0E, 0x0F, 0x10, 0x10, 0x10, 0x0F, 0x0E, 0x07, 0x07, 0x7C, 0x0F, 0x10, 0x10, 0x10, 0x0F, 0x1C, 0x07, 0x00, 0x00, 0x00, 0x2D, 0x8F, 0x87, 0x8F, 0x34, 0x90, 0x90, 0x00, 0x00, 0x0C, 0x14, 0x10, 0x10, 0x10, 0x10, 0x14, 0x0C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0C, 0x14, 0x10, 0x10, 0x10, 0x10, 0x14, 0x0C, 0x00, 0x07, 0x0E, 0x0F, 0x10, 0x10, 0x10, 0x0F, 0x1C, 0x07, 0x00, 0x07, 0x1C, 0x0F, 0x10, 0x10, 0x10, 0x0F, 0x0E, 0x07, 0x00, 0x07, 0x0E, 0x0F, 0x10, 0x10, 0x10, 0x0F, 0x0E, 0x07, 0x00, 0x07, 0x0E, 0x0F, 0x10, 0x10, 0x10, 0x0F, 0x0E, 0x07, 0x00, 0x07, 0x0E, 0x0F, 0x10, 0x10, 0x10, 0x0F, 0x0E, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x0E, 0x0F, 0x10, 0x10, 0x10, 0x14, 0x0C, 0x02, 0x5B, 0x0A, 0x10, 0x10, 0x10, 0x10, 0x10, 0x0A, 0x5B, 0x02, 0x0C, 0x14, 0x10, 0x10, 0x10, 0x0F, 0x0E, 0x07, 0x00, 0x07, 0x0E, 0x0F, 0x10, 0x10, 0x10, 0x0F, 0x0E, 0x07, 0x02, 0x5B, 0x91, 0x10, 0x10, 0x10, 0x25, 0x92, 0x70, 0x00, 0x00, 0x1D, 0x93, 0x94, 0x5F, 0x09, 0x95, 0x96, 0x97, 0x90, 0x00, 0x0C, 0x14, 0x10, 0x10, 0x10, 0x10, 0x14, 0x0C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0C, 0x14, 0x10, 0x10, 0x10, 0x10, 0x14, 0x0C, 0x00, 0x07, 0x0E, 0x0F, 0x10, 0x10, 0x10, 0x25, 0x92, 0x70, 0x01, 0x70, 0x92, 0x25, 0x10, 0x10, 0x10, 0x0F, 0x0E, 0x07, 0x00, 0x07, 0x0E, 0x0F, 0x10, 0x10, 0x10, 0x0F, 0x0E, 0x07, 0x00, 0x07, 0x0E, 0x0F, 0x10, 0x10, 0x10, 0x0F, 0x0E, 0x07, 0x00, 0x07, 0x0E, 0x0F, 0x10, 0x10, 0x10, 0x0F, 0x0E, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x0E, 0x0F, 0x10, 0x10, 0x10, 0x14, 0x0C, 0x00, 0x43, 0x49, 0x10, 0x10, 0x10, 0x10, 0x10, 0x49, 0x43, 0x00, 0x0C, 0x14, 0x10, 0x10, 0x10, 0x0F, 0x0E, 0x07, 0x00, 0x07, 0x0E, 0x0F, 0x10, 0x10, 0x10, 0x0F, 0x0E, 0x07, 0x00, 0x98, 0x33, 0x32, 0x10, 0x10, 0x10, 0x39, 0x99, 0x64, 0x9A, 0x9B, 0x9C, 0x25, 0x10, 0x10, 0x9D, 0x3A, 0x9E, 0x23, 0x00, 0x0C, 0x14, 0x10, 0x10, 0x10, 0x10, 0x14, 0x0C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0C, 0x14, 0x10, 0x10, 0x10, 0x10, 0x14, 0x0C, 0x00, 0x07, 0x0E, 0x0F, 0x10, 0x10, 0x10, 0x10, 0x39, 0x05, 0x9F, 0x05, 0x39, 0x10, 0x10, 0x10, 0x10, 0x0F, 0x0E, 0x07, 0x00, 0x07, 0x0E, 0x0F, 0x10, 0x10, 0x10, 0x0F, 0x0E, 0x07, 0x00, 0x07, 0x0E, 0x0F, 0x10, 0x10, 0x10, 0x0F, 0x0E, 0x07, 0x00, 0x07, 0x0E, 0x0F, 0x10, 0x10, 0x10, 0x0F, 0x0E, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x0E, 0x0F, 0x10, 0x10, 0x10, 0x14, 0x0C, 0x00, 0x34, 0x33, 0x32, 0x10, 0x10, 0x10, 0x32, 0x33, 0x34, 0x00, 0x0C, 0x14, 0x10, 0x10, 0x10, 0x0F, 0x0E, 0x07, 0x00, 0x07, 0x0E, 0x0F, 0x10, 0x10, 0x10, 0x0F, 0x0E, 0x07, 0x00, 0x02, 0xA0, 0x3A, 0x10, 0x10, 0x10, 0x10, 0x7A, 0x42, 0xA1, 0xA2, 0xA3, 0x10, 0x10, 0x10, 0x10, 0xA4, 0x5C, 0x2E, 0x00, 0x0C, 0x14, 0x10, 0x10, 0x10, 0x10, 0x14, 0x0C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0C, 0x14, 0x10, 0x10, 0x10, 0x10, 0x14, 0x0C, 0x00, 0x07, 0x0E, 0x0F, 0x10, 0x10, 0x10, 0x10, 0x10, 0x1B, 0x3B, 0x1B, 0x10, 0x10, 0x10, 0x10, 0x10, 0x0F, 0x0E, 0x07, 0x00, 0x07, 0x0E, 0x0F, 0x10, 0x10, 0x10, 0x0F, 0x0E, 0x07, 0x00, 0x07, 0x0E, 0x0F, 0x10, 0x10, 0x10, 0x0F, 0x0E, 0x07, 0x00, 0x07, 0x0E, 0x0F, 0x10, 0x10, 0x10, 0x0F, 0x0E, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x0E, 0x0F, 0x10, 0x10, 0x10, 0x14, 0x0C, 0x00, 0x07, 0x1C, 0x0F, 0x10, 0x10, 0x10, 0x0F, 0x1C, 0x07, 0x00, 0x0C, 0x14, 0x10, 0x10, 0x10, 0x0F, 0x0E, 0x07, 0x00, 0x07, 0x0E, 0x0F, 0x10, 0x10, 0x10, 0x0F, 0x0E, 0x07, 0x00, 0x00, 0x98, 0x7A, 0x41, 0x10, 0x10, 0x10, 0x10, 0xA3, 0xA3, 0x25, 0x10, 0x10, 0x10, 0x10, 0x12, 0xA5, 0x9A, 0x00, 0x00, 0x0C, 0x14, 0x10, 0x10, 0x10, 0x10, 0x14, 0x0C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0C, 0x14, 0x10, 0x10, 0x10, 0x10, 0x14, 0x0C, 0x00, 0x07, 0x0E, 0x0F, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0xA6, 0x10, 0x10, 0x10, 0x10, 0x0F, 0x0E, 0x07, 0x00, 0x07, 0x0E, 0x0F, 0x10, 0x10, 0x10, 0x0F, 0x0E, 0x07, 0x00, 0x07, 0x0E, 0x0F, 0x10, 0x10, 0x10, 0x0F, 0x0E, 0x07, 0x00, 0x07, 0x0E, 0x0F, 0x10, 0x10, 0x10, 0x0F, 0x0E, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xA7, 0x3A, 0x25, 0x25, 0x25, 0xA8, 0x0C, 0x00, 0x1D, 0x1C, 0x91, 0x25, 0x25, 0x25, 0x91, 0x1C, 0x1D, 0x00, 0x0C, 0xA8, 0x25, 0x25, 0x25, 0x3A, 0xA7, 0x07, 0x00, 0x07, 0xA7, 0x3A, 0x25, 0x25, 0x25, 0x3A, 0xA7, 0x07, 0x00, 0x00, 0x01, 0xA9, 0x32, 0x5F, 0x25, 0xA6, 0x10, 0x10, 0x10, 0x10, 0x10, 0xA6, 0x25, 0x57, 0xAA, 0x77, 0x00, 0x00, 0x00, 0x0C, 0xA8, 0x25, 0x25, 0x25, 0x25, 0xA8, 0x0C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0C, 0xA8, 0x25, 0x25, 0x25, 0x25, 0xA8, 0x0C, 0x00, 0x07, 0x0E, 0x0F, 0x10, 0x10, 0x10, 0x10, 0xA3, 0xA6, 0x10, 0x25, 0x92, 0x63, 0x25, 0x25, 0x25, 0x3A, 0xA7, 0x07, 0x00, 0x07, 0xA7, 0x3A, 0x25, 0x25, 0x25, 0x3A, 0xA7, 0x07, 0x00, 0x07, 0xA7, 0x3A, 0x25, 0x25, 0x25, 0x3A, 0xA7, 0x07, 0x00, 0x07, 0xA7, 0x3A, 0x25, 0x25, 0x25, 0x3A, 0xA7, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1D, 0x0B, 0x25, 0x9C, 0x9C, 0x9C, 0x1B, 0xAB, 0x00, 0x00, 0x98, 0x1B, 0x9C, 0x9C, 0x9C, 0x1B, 0x98, 0x00, 0x00, 0xAB, 0x1B, 0x9C, 0x9C, 0x9C, 0x25, 0x0B, 0x1D, 0x00, 0x1D, 0x0B, 0x25, 0x9C, 0x9C, 0x9C, 0x25, 0x0B, 0x1D, 0x00, 0x00, 0x00, 0x01, 0xAC, 0xAD, 0x25, 0x25, 0x91, 0x0A, 0x0A, 0x0A, 0x91, 0x25, 0x25, 0xAD, 0x0C, 0x00, 0x00, 0x00, 0x00, 0xAB, 0x1B, 0x9C, 0x9C, 0x9C, 0x9C, 0x1B, 0xAB, 0x00, 0x00, 0x00, 0x00, 0x00, 0xAB, 0x1B, 0x9C, 0x9C, 0x9C, 0x9C, 0x1B, 0xAB, 0x00, 0x07, 0x0E, 0x0F, 0x10, 0x10, 0x10, 0xA3, 0xAE, 0x19, 0x5F, 0x0A, 0xAF, 0x25, 0x9C, 0x9C, 0x9C, 0x25, 0x0B, 0x1D, 0x00, 0x1D, 0x0B, 0x25, 0x9C, 0x9C, 0x9C, 0x25, 0x0B, 0x1D, 0x00, 0x1D, 0x0B, 0x25, 0x9C, 0x9C, 0x9C, 0x25, 0x0B, 0x1D, 0x00, 0x1D, 0x0B, 0x25, 0x9C, 0x9C, 0x9C, 0x25, 0x0B, 0x1D, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1D, 0xAB, 0xAB, 0xAB, 0xAB, 0xAB, 0x00, 0x00, 0x00, 0x00, 0xAB, 0xAB, 0xAB, 0xAB, 0xAB, 0x00, 0x00, 0x00, 0x00, 0xAB, 0xAB, 0xAB, 0xAB, 0xAB, 0x1D, 0x00, 0x00, 0x00, 0x1D, 0xAB, 0xAB, 0xAB, 0xAB, 0xAB, 0x1D, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x22, 0x5D, 0xB0, 0xB1, 0xB2, 0xB2, 0xB2, 0xB1, 0xB0, 0x5D, 0x22, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xAB, 0xAB, 0xAB, 0xAB, 0xAB, 0xAB, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xAB, 0xAB, 0xAB, 0xAB, 0xAB, 0xAB, 0x00, 0x00, 0x07, 0x0E, 0x0F, 0x10, 0x10, 0x10, 0x0F, 0x1C, 0xB3, 0xB4, 0xB0, 0x9B, 0xAB, 0xAB, 0xAB, 0xAB, 0xAB, 0x1D, 0x00, 0x00, 0x00, 0x1D, 0xAB, 0xAB, 0xAB, 0xAB, 0xAB, 0x1D, 0x00, 0x00, 0x00, 0x1D, 0xAB, 0xAB, 0xAB, 0xAB, 0xAB, 0x1D, 0x00, 0x00, 0x00, 0x1D, 0xAB, 0xAB, 0xAB, 0xAB, 0xAB, 0x1D, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x22, 0x22, 0x22, 0x22, 0x22, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x0E, 0x0F, 0x10, 0x10, 0x10, 0x0F, 0x0E, 0x90, 0x22, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x0E, 0x0F, 0x10, 0x10, 0x10, 0x0F, 0x0E, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x0E, 0x0F, 0x10, 0x10, 0x10, 0x0F, 0x0E, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xB5, 0xB6, 0x11, 0x11, 0x11, 0xB6, 0xB5, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x6A, 0x6C, 0x33, 0x33, 0x33, 0x6C, 0x6A, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x13, 0x13, 0x13, 0x13, 0x13, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

const GUI_BITMAP bmMicriumLogo = {
 145, /* XSize */
 39, /* YSize */
 145, /* BytesPerLine */
 8, /* BitsPerPixel */
 acMicriumLogo,  /* Pointer to picture data (indices) */
 &PalMicriumLogo  /* Pointer to palette */
};

/* *** End of file *** */
	 	 			 		    	 				 	  			   	 	 	 	 	 	  	  	      	   		 	 	 		  		  	 		 	  	  			     			       	   	 			  		    	 	     	 				  	 					 	 			   	  	  			 				 		 	 	 			     			 
