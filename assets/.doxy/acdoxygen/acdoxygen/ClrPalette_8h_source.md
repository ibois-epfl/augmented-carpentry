

# File ClrPalette.h

[**File List**](files.md) **>** [**AIAC**](dir_21da83368f7816722f2b707a7b03c84f.md) **>** [**UI**](dir_1ecaf06ce723c740944fb523b6bd2c55.md) **>** [**ClrPalette.h**](ClrPalette_8h.md)

[Go to the documentation of this file](ClrPalette_8h.md)


```C++
// #####################################################################
// >>>>>>>>>>>>>>>>>>>>> BEGINNING OF LEGAL NOTICE >>>>>>>>>>>>>>>>>>>>>
//######################################################################
//
// This source file, along with its associated content, was authored by
// Andrea Settimi, Hong-Bin Yang, Naravich Chutisilp, and numerous other
// contributors. The code was originally developed at the Laboratory for
// Timber Construction (IBOIS, director: Prof. Yves Weinand) at the School of 
// Architecture, Civil and Environmental Engineering (ENAC) at the Swiss
// Federal Institute of Technology in Lausanne (EPFL) for the Doctoral
// Research "Augmented Carpentry" (PhD researcher: Andrea Settimi,
// co-director: Dr. Julien Gamerro, director: Prof. Yves Weinand).
//
// Although the entire repository is distributed under the GPL license,
// these particular source files may also be used under the terms of the
// MIT license. By accessing or using this file, you agree to the following:
//
// 1. You may reproduce, modify, and distribute this file in accordance
//    with the terms of the MIT license.
// 2. You must retain this legal notice in all copies or substantial
//    portions of this file.
// 3. This file is provided "AS IS," without any express or implied
//    warranties, including but not limited to the implied warranties of
//    merchantability and fitness for a particular purpose.
//
// If you cannot or will not comply with the above conditions, you are
// not permitted to use this file. By proceeding, you acknowledge and
// accept all terms and conditions herein.
//
//######################################################################
// <<<<<<<<<<<<<<<<<<<<<<< END OF LEGAL NOTICE <<<<<<<<<<<<<<<<<<<<<<<<
// #####################################################################
//
#pragma once

// define macros for colors
#define AIAC_UI_RED ImVec4(1.0f, 0.0f, 0.0f, 1.0f)
#define AIAC_UI_GREEN ImVec4(0.0f, 1.0f, 0.0f, 1.0f)
#define AIAC_UI_DARK_GREEN ImVec4(0.0f, 0.5f, 0.0f, 1.0f)
#define AIAC_UI_BLUE ImVec4(0.0f, 0.0f, 1.0f, 1.0f)
#define AIAC_UI_YELLOW ImVec4(1.0f, 1.0f, 0.0f, 1.0f)
#define AIAC_UI_CYAN ImVec4(0.0f, 1.0f, 1.0f, 1.0f)
#define AIAC_UI_MAGENTA ImVec4(1.0f, 0.0f, 1.0f, 1.0f)
#define AIAC_UI_WHITE ImVec4(1.0f, 1.0f, 1.0f, 1.0f)
#define AIAC_UI_BLACK ImVec4(0.0f, 0.0f, 0.0f, 1.0f)
#define AIAC_UI_GREY ImVec4(0.5f, 0.5f, 0.5f, 1.0f)
#define AIAC_UI_PURPLE ImVec4(0.5f, 0.0f, 0.5f, 1.0f)
#define AIAC_UI_LIGHT_GREY ImVec4(0.5f, 0.5f, 0.5f, 1.0f)
#define AIAC_UI_DARK_GREY ImVec4(0.2f, 0.2f, 0.2f, 1.0f)
#define AIAC_UI_LIGHT_RED ImVec4(1.0f, 0.4f, 0.4f, 1.0f)
#define AIAC_UI_LIGHT_GREEN ImVec4(0.4f, 1.0f, 0.4f, 1.0f)
#define AIAC_UI_LIGHT_BLUE ImVec4(0.4f, 0.4f, 1.0f, 1.0f)
#define AIAC_UI_LIGHT_YELLOW ImVec4(1.0f, 1.0f, 0.4f, 1.0f)
#define AIAC_UI_LIGHT_CYAN ImVec4(0.4f, 1.0f, 1.0f, 1.0f)
#define AIAC_UI_LIGHT_MAGENTA ImVec4(1.0f, 0.4f, 1.0f, 1.0f)
#define AIAC_UI_LIGHT_WHITE ImVec4(1.0f, 1.0f, 1.0f, 1.0f)
#define AIAC_UI_LIGHT_BLACK ImVec4(0.4f, 0.4f, 0.4f, 1.0f)
#define AIAC_UI_SPARK_ORANGE ImVec4(1.0f, 0.2f, 0.0f, 1.0f)
#define AIAC_UI_SEA_GREEN ImVec4(0.18f, 0.545f, 0.341f, 1.0f)
#define AIAC_UI_GRAPE_PURPLE ImVec4(0.56f, 0.35f, 0.62f, 1.0f)
#define AIAC_UI_CARMINE_RED ImVec4(0.59f, 0.0f, 0.09f, 1.0f)
#define AIAC_UI_YALE_BLUE ImVec4(0.06f, 0.3f, 0.57f, 1.0f)
#define AIAC_UI_HIBISCUS_RED ImVec4(0.79f, 0.0f, 0.09f, 1.0f)
#define AIAC_UI_ROYAL_PURPLE ImVec4(0.4f, 0.0f, 0.6f, 1.0f)
#define AIAC_UI_LOLLIPOP_PURPLE ImVec4(0.6f, 0.0f, 0.6f, 1.0f)
#define AIAC_UI_PLUM_PURPLE ImVec4(0.56f, 0.27f, 0.52f, 1.0f)
#define AIAC_UI_EGYPTIAN_BLUE ImVec4(0.06f, 0.2f, 0.65f, 1.0f)
#define AIAC_UI_SAPPHIRE_BLUE ImVec4(0.06f, 0.32f, 0.73f, 1.0f)
#define AIAC_UI_PRUSSIAN_BLUE ImVec4(0.0f, 0.19f, 0.33f, 1.0f)
#define AIAC_UI_CINNAMON_RED ImVec4(0.82f, 0.41f, 0.12f, 1.0f)
#define AIAC_UI_APRICOT_ORANGE ImVec4(0.98f, 0.81f, 0.69f, 1.0f)
#define AIAC_UI_BRONZE_ORANGE ImVec4(0.8f, 0.5f, 0.2f, 1.0f)
```


