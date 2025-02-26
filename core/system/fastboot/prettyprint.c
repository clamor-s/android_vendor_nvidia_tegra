/*
 * Copyright (c) 2012-2013, NVIDIA CORPORATION.  All rights reserved.
 *
 * NVIDIA CORPORATION and its licensors retain all intellectual property
 * and proprietary rights in and to this software, related documentation
 * and any modifications thereto.  Any use, reproduction, disclosure or
 * distribution of this software and related documentation without an express
 * license agreement from NVIDIA CORPORATION is strictly prohibited.
 */

#include "prettyprint.h"
#include "fastboot.h"
#include "nvassert.h"
#include "nvodm_query.h"

#ifndef DISP_FONT_SCALE
#define DISP_FONT_SCALE 1
#endif
#define DISP_FONT_WIDTH 8
#define DISP_FONT_HEIGHT 8
#define DISP_FONT_WIDTH_SCALED (DISP_FONT_WIDTH * DISP_FONT_SCALE)
#define DISP_FONT_HEIGHT_SCALED (DISP_FONT_HEIGHT * DISP_FONT_SCALE)
static NvU32                  s_StatusColor = 0xffff;
static NvU32                  s_ErrorColor  = 0xf800;
static NvU32                  s_32bStatusColor = 0xffffff;
static NvU32                  s_32bErrorColor = 0xff0000;
static NvU32                  s_32bStatusColor_abgr = 0xffffff;
static NvU32                  s_32bErrorColor_abgr = 0xff;
static NvU32                  s_SelectedMenuColor =0x33ff33;
static NvU32                  s_32bSelectedMenuColor = 0x33ff33;
static NvU32                  s_32bSelectedMenuColor_abgr = 0x33ff33;

static const NvU8  g_font[] = {
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, /*' '*/
    0x18,0x18,0x18,0x18,0x18,0x00,0x18,0x00, /*'!'*/
    0x00,0x24,0x24,0x00,0x00,0x00,0x00,0x00, /*'"'*/
    0x36,0x36,0x7F,0x36,0x7F,0x36,0x36,0x00, /*'#'*/
    0x0C,0x3F,0x68,0x3E,0x0B,0x7E,0x18,0x00, /*'$'*/
    0x60,0x66,0x0C,0x18,0x30,0x66,0x06,0x00, /*'%'*/
    0x38,0x6C,0x6C,0x38,0x6D,0x66,0x3B,0x00, /*'&'*/
    0x18,0x18,0x18,0x00,0x00,0x00,0x00,0x00, /*'''*/
    0x0C,0x18,0x30,0x30,0x30,0x18,0x0C,0x00, /*'('*/
    0x30,0x18,0x0C,0x0C,0x0C,0x18,0x30,0x00, /*')'*/
    0x00,0x18,0x7E,0x3C,0x7E,0x18,0x00,0x00, /*'*'*/
    0x00,0x18,0x18,0x7E,0x18,0x18,0x00,0x00, /*'+'*/
    0x00,0x00,0x00,0x00,0x00,0x18,0x18,0x30, /*','*/
    0x00,0x00,0x00,0x7E,0x00,0x00,0x00,0x00, /*'-'*/
    0x00,0x00,0x00,0x00,0x00,0x18,0x18,0x00, /*'.'*/
    0x00,0x06,0x0C,0x18,0x30,0x60,0x00,0x00, /*'/'*/
    0x00,0x3C,0x46,0x4A,0x52,0x62,0x3C,0x00, /*'0'*/
    0x00,0x18,0x28,0x08,0x08,0x08,0x3E,0x00, /*'1'*/
    0x00,0x3C,0x42,0x02,0x3C,0x40,0x7E,0x00, /*'2'*/
    0x00,0x3C,0x42,0x0C,0x02,0x42,0x3C,0x00, /*'3'*/
    0x00,0x08,0x18,0x28,0x48,0x7E,0x08,0x00, /*'4'*/
    0x00,0x7E,0x40,0x7C,0x02,0x42,0x3C,0x00, /*'5'*/
    0x00,0x3C,0x40,0x7C,0x42,0x42,0x3C,0x00, /*'6'*/
    0x00,0x7E,0x02,0x04,0x08,0x10,0x10,0x00, /*'7'*/
    0x00,0x3C,0x42,0x3C,0x42,0x42,0x3C,0x00, /*'8'*/
    0x00,0x3C,0x42,0x42,0x3E,0x02,0x3C,0x00, /*'9'*/
    0x00,0x00,0x00,0x10,0x00,0x00,0x10,0x00, /*':'*/
    0x00,0x00,0x18,0x18,0x00,0x18,0x18,0x30, /*';'*/
    0x0C,0x18,0x30,0x60,0x30,0x18,0x0C,0x00, /*'<'*/
    0x00,0x00,0x7E,0x00,0x7E,0x00,0x00,0x00, /*'='*/
    0x30,0x18,0x0C,0x06,0x0C,0x18,0x30,0x00, /*'>'*/
    0x3C,0x66,0x0C,0x18,0x18,0x00,0x18,0x00, /*'?'*/
    0x3C,0x66,0x6E,0x6A,0x6E,0x60,0x3C,0x00, /*'@'*/
    0x00,0x3C,0x42,0x42,0x7E,0x42,0x42,0x00, /*'A'*/
    0x00,0x7C,0x42,0x7C,0x42,0x42,0x7C,0x00, /*'B'*/
    0x00,0x3C,0x42,0x40,0x40,0x42,0x3C,0x00, /*'C'*/
    0x00,0x78,0x44,0x42,0x42,0x44,0x78,0x00, /*'D'*/
    0x00,0x7E,0x40,0x7C,0x40,0x40,0x7E,0x00, /*'E'*/
    0x00,0x7E,0x40,0x7C,0x40,0x40,0x40,0x00, /*'F'*/
    0x00,0x3C,0x42,0x40,0x4E,0x42,0x3C,0x00, /*'G'*/
    0x00,0x42,0x42,0x7E,0x42,0x42,0x42,0x00, /*'H'*/
    0x00,0x3E,0x08,0x08,0x08,0x08,0x3E,0x00, /*'I'*/
    0x00,0x02,0x02,0x02,0x42,0x42,0x3C,0x00, /*'J'*/
    0x00,0x48,0x50,0x60,0x50,0x48,0x44,0x00, /*'K'*/
    0x00,0x40,0x40,0x40,0x40,0x40,0x7E,0x00, /*'L'*/
    0x00,0x42,0x66,0x5A,0x42,0x42,0x42,0x00, /*'M'*/
    0x00,0x42,0x62,0x52,0x4A,0x46,0x42,0x00, /*'N'*/
    0x00,0x3C,0x42,0x42,0x42,0x42,0x3C,0x00, /*'O'*/
    0x00,0x7C,0x42,0x42,0x7C,0x40,0x40,0x00, /*'P'*/
    0x00,0x3C,0x42,0x42,0x52,0x4A,0x3C,0x00, /*'Q'*/
    0x00,0x7C,0x42,0x42,0x7C,0x44,0x42,0x00, /*'R'*/
    0x00,0x3C,0x40,0x3C,0x02,0x42,0x3C,0x00, /*'S'*/
    0x00,0x7F,0x08,0x08,0x08,0x08,0x08,0x00, /*'T'*/
    0x00,0x42,0x42,0x42,0x42,0x42,0x3C,0x00, /*'U'*/
    0x00,0x42,0x42,0x42,0x42,0x24,0x18,0x00, /*'V'*/
    0x00,0x42,0x42,0x42,0x42,0x5A,0x24,0x00, /*'W'*/
    0x00,0x42,0x24,0x18,0x18,0x24,0x42,0x00, /*'X'*/
    0x00,0x41,0x22,0x14,0x08,0x08,0x08,0x00, /*'Y'*/
    0x00,0x7E,0x04,0x08,0x10,0x20,0x7E,0x00, /*'Z'*/
    0x7C,0x60,0x60,0x60,0x60,0x60,0x7C,0x00, /*'['*/
    0x00,0x60,0x30,0x18,0x0C,0x06,0x00,0x00, /*'\'*/
    0x3E,0x06,0x06,0x06,0x06,0x06,0x3E,0x00, /*']'*/
    0x3C,0x66,0x00,0x00,0x00,0x00,0x00,0x00, /*'^'*/
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF, /*'_'*/
    0x30,0x18,0x00,0x00,0x00,0x00,0x00,0x00, /*'`'*/
    0x00,0x00,0x38,0x04,0x3C,0x44,0x3C,0x00, /*'a'*/
    0x00,0x40,0x40,0x78,0x44,0x44,0x78,0x00, /*'b'*/
    0x00,0x00,0x1C,0x20,0x20,0x20,0x1C,0x00, /*'c'*/
    0x00,0x04,0x04,0x3C,0x44,0x44,0x3C,0x00, /*'d'*/
    0x00,0x00,0x38,0x44,0x78,0x40,0x3C,0x00, /*'e'*/
    0x00,0x18,0x20,0x30,0x20,0x20,0x20,0x00, /*'f'*/
    0x00,0x00,0x3C,0x44,0x44,0x3C,0x04,0x38, /*'g'*/
    0x00,0x20,0x20,0x3C,0x22,0x22,0x22,0x00, /*'h'*/
    0x00,0x10,0x00,0x30,0x10,0x10,0x38,0x00, /*'i'*/
    0x00,0x08,0x00,0x08,0x08,0x08,0x48,0x30, /*'j'*/
    0x00,0x40,0x50,0x60,0x60,0x50,0x48,0x00, /*'k'*/
    0x00,0x20,0x20,0x20,0x20,0x20,0x18,0x00, /*'l'*/
    0x00,0x00,0x68,0x54,0x54,0x44,0x44,0x00, /*'m'*/
    0x00,0x00,0x78,0x44,0x44,0x44,0x44,0x00, /*'n'*/
    0x00,0x00,0x38,0x44,0x44,0x44,0x38,0x00, /*'o'*/
    0x00,0x00,0x78,0x44,0x44,0x78,0x40,0x40, /*'p'*/
    0x00,0x00,0x3C,0x44,0x44,0x3C,0x04,0x06, /*'q'*/
    0x00,0x00,0x1C,0x20,0x20,0x20,0x20,0x00, /*'r'*/
    0x00,0x00,0x38,0x40,0x38,0x04,0x78,0x00, /*'s'*/
    0x00,0x10,0x38,0x10,0x10,0x10,0x0C,0x00, /*'t'*/
    0x00,0x00,0x44,0x44,0x44,0x44,0x38,0x00, /*'u'*/
    0x00,0x00,0x44,0x44,0x28,0x28,0x10,0x00, /*'v'*/
    0x00,0x00,0x44,0x44,0x44,0x54,0x28,0x00, /*'w'*/
    0x00,0x00,0x44,0x28,0x10,0x28,0x44,0x00, /*'x'*/
    0x00,0x00,0x44,0x44,0x44,0x3C,0x04,0x38, /*'y'*/
    0x00,0x00,0x7C,0x08,0x10,0x20,0x7C,0x00, /*'z'*/
    0x0C,0x18,0x18,0x70,0x18,0x18,0x0C,0x00, /*'{'*/
    0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x00, /*'|'*/
    0x30,0x18,0x18,0x0E,0x18,0x18,0x30,0x00, /*'}'*/
    0x31,0x6B,0x46,0x00,0x00,0x00,0x00,0x00, /*'~'*/
    0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF, /*''*/
};

#define SWAP(a, b) {                            \
    (a) ^= (b);                                 \
    (b) ^= (a);                                 \
    (a) ^= (b);                                 \
}

static void SurfaceRead(
    NvRmSurface *pSurf,
    NvU32 x,
    NvU32 y,
    NvU32 Width,
    NvU32 Height,
    void *pSrcPixels)
{
    NvU32 rotateangle = NvOdmQueryRotateDisplay();

    switch (rotateangle) {
    case 90:
        SWAP(x, y);
        SWAP(Width, Height);
        x = pSurf->Width - x - 1 - Width;
        break;
    case 180:
        y = pSurf->Height - y - 1 - Height;
        x = pSurf->Width - x - 1 - Width;
        break;
    case 270:
        SWAP(x, y);
        SWAP(Width, Height);
        y = pSurf->Height - y - 1 - Height;
        break;
    default:
        break;
    }

    NvRmSurfaceRead(pSurf, x, y, Width, Height, pSrcPixels);
}

static void SurfaceWrite(
    NvRmSurface *pSurf,
    NvU32 x,
    NvU32 y,
    NvU32 Width,
    NvU32 Height,
    const void *pSrcPixels)
{
    NvU32 rotateangle = NvOdmQueryRotateDisplay();

    switch (rotateangle) {
    case 90:
        SWAP(x, y);
        SWAP(Width, Height);
        x = pSurf->Width - x - 1 - Width;
        break;
    case 180:
        y = pSurf->Height - y - 1 - Height;
        x = pSurf->Width - x - 1 - Width;
        break;
    case 270:
        SWAP(x, y);
        SWAP(Width, Height);
        y = pSurf->Height - y - 1 - Height;
        break;
    default:
        break;
    }

    NvRmSurfaceWrite(pSurf, x, y, Width, Height, pSrcPixels);
}

static void
PrettyPrintLinefeed( NvRmSurface *surf )
{
    NvU32 i;
    NvU32 size = surf->Width * surf->Pitch * DISP_FONT_HEIGHT_SCALED;
    void *line = NvOsAlloc( size );
    NV_ASSERT( line );

    for( i = DISP_FONT_HEIGHT_SCALED; i < surf->Height; i += DISP_FONT_HEIGHT_SCALED )
    {
        SurfaceRead( surf, 0, i, surf->Width, DISP_FONT_HEIGHT_SCALED, line );
        SurfaceWrite( surf, 0, i - DISP_FONT_HEIGHT_SCALED, surf->Width,
            DISP_FONT_HEIGHT_SCALED, line );
    }

    NvOsMemset( line, 0, size );
    SurfaceWrite( surf, 0, surf->Height - DISP_FONT_HEIGHT_SCALED,
        surf->Width, DISP_FONT_HEIGHT_SCALED, line );

    NvOsFree( line );
}

void
PrettyPrintf( PrettyPrintContext *context, NvRmSurface *surf,
    NvU32 condition, const char *format, ... )
{
#ifndef BUILD_FOR_COSIM // display is disabled in main.c
    va_list ap;
    NvU32 i, j, k, l, m;
    NvU32 len;
    NvU8 *font;
    char msg[128];
    NvU32 rotateangle = NvOdmQueryRotateDisplay();

    if( !surf )
    {
        return;
    }

    va_start( ap, format );
    NvOsVsnprintf( msg, sizeof(msg), format, ap );

    NV_DEBUG_PRINTF(( "testdisp print: %s", msg ));

    len = NvOsStrlen( msg );
    for( i = 0; i < len; i++ )
    {
        NvU32 index;

        if( msg[i] == '\n' || context->y >= surf->Height )
        {
            context->x = 0;
            context->y += DISP_FONT_HEIGHT_SCALED;
            if( context->y >= surf->Height )
            {
                PrettyPrintLinefeed( surf );
                context->y = surf->Height - DISP_FONT_HEIGHT_SCALED;
            }

            if( msg[i] == '\n' )
            {
                continue;
            }
        }

        index = msg[i] - ' ';
        font = (NvU8 *)&g_font[ index * DISP_FONT_HEIGHT ];

        if (surf->ColorFormat == NvColorFormat_A8R8G8B8)
        {
            NvU32 pixels[DISP_FONT_WIDTH_SCALED * DISP_FONT_HEIGHT_SCALED];
            NvU32 color = 0;

            if (condition == FASTBOOT_ERROR)
                color = s_32bErrorColor;
            else if (condition == FASTBOOT_STATUS)
                color = s_32bStatusColor;
            else if (condition == FASTBOOT_SELECTED_MENU)
                color = s_32bSelectedMenuColor;

            for( j = 0; j < DISP_FONT_HEIGHT; j++ )
            {
                for( k = 0; k < DISP_FONT_WIDTH; k++ )
                {
                    NvU32 pixel = 0;

                    if( ((*font) >> (DISP_FONT_WIDTH - k)) & 0x1 )
                    {
                        pixel = color;
                    }
                    for ( l = 0; l < DISP_FONT_SCALE; l++ )
                    {
                        for ( m = 0; m < DISP_FONT_SCALE; m++ )
                        {
                            pixels[((j * DISP_FONT_SCALE) * DISP_FONT_HEIGHT_SCALED)
                                + (l * DISP_FONT_WIDTH_SCALED)
                                + ((k * DISP_FONT_SCALE) + m)] = pixel;
                        }
                    }
                }

                font++;
            }
            SurfaceWrite( surf, context->x, context->y, DISP_FONT_WIDTH_SCALED,
            DISP_FONT_HEIGHT_SCALED, pixels );
        }
        else if (surf->ColorFormat == NvColorFormat_A8B8G8R8)
        {
            NvU32 pixels[DISP_FONT_WIDTH_SCALED * DISP_FONT_HEIGHT_SCALED];
            NvU32 color = 0;

            if (condition == FASTBOOT_ERROR)
                color = s_32bErrorColor_abgr;
            else if (condition == FASTBOOT_STATUS)
                color = s_32bStatusColor_abgr;
            else if (condition == FASTBOOT_SELECTED_MENU)
                color = s_32bSelectedMenuColor_abgr;

            for( j = 0; j < DISP_FONT_HEIGHT; j++ )
            {
                for( k = 0; k < DISP_FONT_WIDTH; k++ )
                {
                    NvU32 pixel = 0;
                    NvU32 index = 0;
                    NvU32 x, y;

                    if( ((*font) >> (DISP_FONT_WIDTH - k)) & 0x1)
                    {
                        pixel = color;
                    }

                    switch (rotateangle)
                    {
                        case 90:
                            index = (k * DISP_FONT_HEIGHT) + (DISP_FONT_HEIGHT - 1) - j;
                            break;
                        case 270:
                            index = (( DISP_FONT_HEIGHT - k - 1) * DISP_FONT_HEIGHT) + j;
                            break;
                        case 180:
                            index = (( DISP_FONT_HEIGHT - j - 1) * DISP_FONT_HEIGHT) + \
                                           (DISP_FONT_WIDTH - 1 - k);
                            break;
                        case 0:
                        default:
                            index = (j * DISP_FONT_HEIGHT) + k;
                            break;
                    }
                    y = index / DISP_FONT_HEIGHT;
                    x = index % DISP_FONT_HEIGHT;
                    for ( l = 0; l < DISP_FONT_SCALE; l++ )
                    {
                        for ( m = 0; m < DISP_FONT_SCALE; m++ )
                        {
                            pixels[((y * DISP_FONT_SCALE) * DISP_FONT_HEIGHT_SCALED)
                                + (l * DISP_FONT_WIDTH_SCALED)
                                + ((x * DISP_FONT_SCALE) + m)] = pixel;
                        }
                    }
                }

                font++;
            }
            SurfaceWrite( surf, context->x, context->y, DISP_FONT_WIDTH_SCALED,
            DISP_FONT_HEIGHT_SCALED, pixels );
        }
        else
        {
            NvU16 pixels[DISP_FONT_WIDTH_SCALED * DISP_FONT_HEIGHT_SCALED];
            NvU16 color = 0;

            if (condition == FASTBOOT_ERROR)
                color = s_ErrorColor;
            else if (condition == FASTBOOT_STATUS)
                color = s_StatusColor;
            else if (condition == FASTBOOT_SELECTED_MENU)
                color = s_SelectedMenuColor;

            for( j = 0; j < DISP_FONT_HEIGHT; j++ )
            {
                for( k = 0; k < DISP_FONT_WIDTH; k++ )
                {
                    NvU16 pixel = 0;

                    if( ((*font) >> (DISP_FONT_WIDTH - k)) & 0x1 )
                    {
                        pixel = color;
                    }
                    for ( l = 0; l < DISP_FONT_SCALE; l++ )
                    {
                        for ( m = 0; m < DISP_FONT_SCALE; m++ )
                        {
                            pixels[((j * DISP_FONT_SCALE) * DISP_FONT_HEIGHT_SCALED)
                                + (l * DISP_FONT_WIDTH_SCALED)
                                + ((k * DISP_FONT_SCALE) + m)] = pixel;
                        }
                    }
                }

                font++;
            }
            SurfaceWrite( surf, context->x, context->y, DISP_FONT_WIDTH_SCALED,
            DISP_FONT_HEIGHT_SCALED, pixels );
        }

        context->x += DISP_FONT_WIDTH_SCALED;
        if( context->x >= surf->Width )
        {
            context->x = 0;
            context->y += DISP_FONT_HEIGHT_SCALED;
        }
    }
    //Flush the WriteCombineBuffer since FrameBuffer Surface memory
    // is WriteCombined alloced
    NvOsFlushWriteCombineBuffer();

    FramebufferUpdate();

    va_end( ap );
#endif
}
