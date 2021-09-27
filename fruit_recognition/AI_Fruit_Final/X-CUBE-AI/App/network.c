/**
  ******************************************************************************
  * @file    network.c
  * @author  AST Embedded Analytics Research Platform
  * @date    Sun Sep 12 17:03:10 2021
  * @brief   AI Tool Automatic Code Generator for Embedded NN computing
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2018 STMicroelectronics.
  * All rights reserved.
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */


#include "network.h"

#include "ai_platform_interface.h"
#include "ai_math_helpers.h"

#include "core_common.h"
#include "layers.h"



#undef AI_TOOLS_VERSION_MAJOR
#undef AI_TOOLS_VERSION_MINOR
#undef AI_TOOLS_VERSION_MICRO
#define AI_TOOLS_VERSION_MAJOR 5
#define AI_TOOLS_VERSION_MINOR 2
#define AI_TOOLS_VERSION_MICRO 0


#undef AI_TOOLS_API_VERSION_MAJOR
#undef AI_TOOLS_API_VERSION_MINOR
#undef AI_TOOLS_API_VERSION_MICRO
#define AI_TOOLS_API_VERSION_MAJOR 1
#define AI_TOOLS_API_VERSION_MINOR 3
#define AI_TOOLS_API_VERSION_MICRO 0

#undef AI_NET_OBJ_INSTANCE
#define AI_NET_OBJ_INSTANCE g_network
 
#undef AI_NETWORK_MODEL_SIGNATURE
#define AI_NETWORK_MODEL_SIGNATURE     "7e3e20377a4062467b64aa2e4d5d6692"

#ifndef AI_TOOLS_REVISION_ID
#define AI_TOOLS_REVISION_ID     "(rev-5.2.0)"
#endif

#undef AI_TOOLS_DATE_TIME
#define AI_TOOLS_DATE_TIME   "Sun Sep 12 17:03:10 2021"

#undef AI_TOOLS_COMPILE_TIME
#define AI_TOOLS_COMPILE_TIME    __DATE__ " " __TIME__

#undef AI_NETWORK_N_BATCHES
#define AI_NETWORK_N_BATCHES         (1)

/**  Forward network declaration section  *************************************/
AI_STATIC ai_network AI_NET_OBJ_INSTANCE;


/**  Forward network array declarations  **************************************/
AI_STATIC ai_array conv2d_7_scratch1_array;   /* Array #0 */
AI_STATIC ai_array conv2d_7_scratch0_array;   /* Array #1 */
AI_STATIC ai_array conv2d_5_scratch1_array;   /* Array #2 */
AI_STATIC ai_array conv2d_5_scratch0_array;   /* Array #3 */
AI_STATIC ai_array conv2d_3_scratch1_array;   /* Array #4 */
AI_STATIC ai_array conv2d_3_scratch0_array;   /* Array #5 */
AI_STATIC ai_array conv2d_1_scratch1_array;   /* Array #6 */
AI_STATIC ai_array conv2d_1_scratch0_array;   /* Array #7 */
AI_STATIC ai_array dense_13_bias_array;   /* Array #8 */
AI_STATIC ai_array dense_13_weights_array;   /* Array #9 */
AI_STATIC ai_array dense_12_bias_array;   /* Array #10 */
AI_STATIC ai_array dense_12_weights_array;   /* Array #11 */
AI_STATIC ai_array dense_11_bias_array;   /* Array #12 */
AI_STATIC ai_array dense_11_weights_array;   /* Array #13 */
AI_STATIC ai_array dense_10_bias_array;   /* Array #14 */
AI_STATIC ai_array dense_10_weights_array;   /* Array #15 */
AI_STATIC ai_array conv2d_7_bias_array;   /* Array #16 */
AI_STATIC ai_array conv2d_7_weights_array;   /* Array #17 */
AI_STATIC ai_array conv2d_5_bias_array;   /* Array #18 */
AI_STATIC ai_array conv2d_5_weights_array;   /* Array #19 */
AI_STATIC ai_array conv2d_3_bias_array;   /* Array #20 */
AI_STATIC ai_array conv2d_3_weights_array;   /* Array #21 */
AI_STATIC ai_array conv2d_1_bias_array;   /* Array #22 */
AI_STATIC ai_array conv2d_1_weights_array;   /* Array #23 */
AI_STATIC ai_array conv2d_4_input_output_array;   /* Array #24 */
AI_STATIC ai_array conversion_0_output_array;   /* Array #25 */
AI_STATIC ai_array conv2d_1_output_array;   /* Array #26 */
AI_STATIC ai_array conv2d_3_output_array;   /* Array #27 */
AI_STATIC ai_array conv2d_5_output_array;   /* Array #28 */
AI_STATIC ai_array conv2d_7_output_array;   /* Array #29 */
AI_STATIC ai_array dense_10_output_array;   /* Array #30 */
AI_STATIC ai_array dense_11_output_array;   /* Array #31 */
AI_STATIC ai_array dense_12_output_array;   /* Array #32 */
AI_STATIC ai_array dense_13_output_array;   /* Array #33 */
AI_STATIC ai_array dense_13_fmt_output_array;   /* Array #34 */
AI_STATIC ai_array nl_14_output_array;   /* Array #35 */
AI_STATIC ai_array nl_14_fmt_output_array;   /* Array #36 */


/**  Forward network tensor declarations  *************************************/
AI_STATIC ai_tensor conv2d_7_scratch1;   /* Tensor #0 */
AI_STATIC ai_tensor conv2d_7_scratch0;   /* Tensor #1 */
AI_STATIC ai_tensor conv2d_5_scratch1;   /* Tensor #2 */
AI_STATIC ai_tensor conv2d_5_scratch0;   /* Tensor #3 */
AI_STATIC ai_tensor conv2d_3_scratch1;   /* Tensor #4 */
AI_STATIC ai_tensor conv2d_3_scratch0;   /* Tensor #5 */
AI_STATIC ai_tensor conv2d_1_scratch1;   /* Tensor #6 */
AI_STATIC ai_tensor conv2d_1_scratch0;   /* Tensor #7 */
AI_STATIC ai_tensor dense_13_bias;   /* Tensor #8 */
AI_STATIC ai_tensor dense_13_weights;   /* Tensor #9 */
AI_STATIC ai_tensor dense_12_bias;   /* Tensor #10 */
AI_STATIC ai_tensor dense_12_weights;   /* Tensor #11 */
AI_STATIC ai_tensor dense_11_bias;   /* Tensor #12 */
AI_STATIC ai_tensor dense_11_weights;   /* Tensor #13 */
AI_STATIC ai_tensor dense_10_bias;   /* Tensor #14 */
AI_STATIC ai_tensor dense_10_weights;   /* Tensor #15 */
AI_STATIC ai_tensor conv2d_7_bias;   /* Tensor #16 */
AI_STATIC ai_tensor conv2d_7_weights;   /* Tensor #17 */
AI_STATIC ai_tensor conv2d_5_bias;   /* Tensor #18 */
AI_STATIC ai_tensor conv2d_5_weights;   /* Tensor #19 */
AI_STATIC ai_tensor conv2d_3_bias;   /* Tensor #20 */
AI_STATIC ai_tensor conv2d_3_weights;   /* Tensor #21 */
AI_STATIC ai_tensor conv2d_1_bias;   /* Tensor #22 */
AI_STATIC ai_tensor conv2d_1_weights;   /* Tensor #23 */
AI_STATIC ai_tensor conv2d_4_input_output;   /* Tensor #24 */
AI_STATIC ai_tensor conversion_0_output;   /* Tensor #25 */
AI_STATIC ai_tensor conv2d_1_output;   /* Tensor #26 */
AI_STATIC ai_tensor conv2d_3_output;   /* Tensor #27 */
AI_STATIC ai_tensor conv2d_5_output;   /* Tensor #28 */
AI_STATIC ai_tensor conv2d_7_output;   /* Tensor #29 */
AI_STATIC ai_tensor conv2d_7_output0;   /* Tensor #30 */
AI_STATIC ai_tensor dense_10_output;   /* Tensor #31 */
AI_STATIC ai_tensor dense_11_output;   /* Tensor #32 */
AI_STATIC ai_tensor dense_12_output;   /* Tensor #33 */
AI_STATIC ai_tensor dense_13_output;   /* Tensor #34 */
AI_STATIC ai_tensor dense_13_fmt_output;   /* Tensor #35 */
AI_STATIC ai_tensor nl_14_output;   /* Tensor #36 */
AI_STATIC ai_tensor nl_14_fmt_output;   /* Tensor #37 */


/**  Forward network tensor chain declarations  *******************************/
AI_STATIC_CONST ai_tensor_chain conversion_0_chain;   /* Chain #0 */
AI_STATIC_CONST ai_tensor_chain conv2d_1_chain;   /* Chain #1 */
AI_STATIC_CONST ai_tensor_chain conv2d_3_chain;   /* Chain #2 */
AI_STATIC_CONST ai_tensor_chain conv2d_5_chain;   /* Chain #3 */
AI_STATIC_CONST ai_tensor_chain conv2d_7_chain;   /* Chain #4 */
AI_STATIC_CONST ai_tensor_chain dense_10_chain;   /* Chain #5 */
AI_STATIC_CONST ai_tensor_chain dense_11_chain;   /* Chain #6 */
AI_STATIC_CONST ai_tensor_chain dense_12_chain;   /* Chain #7 */
AI_STATIC_CONST ai_tensor_chain dense_13_chain;   /* Chain #8 */
AI_STATIC_CONST ai_tensor_chain dense_13_fmt_chain;   /* Chain #9 */
AI_STATIC_CONST ai_tensor_chain nl_14_chain;   /* Chain #10 */
AI_STATIC_CONST ai_tensor_chain nl_14_fmt_chain;   /* Chain #11 */


/**  Forward network layer declarations  **************************************/
AI_STATIC ai_layer_nl conversion_0_layer; /* Layer #0 */
AI_STATIC ai_layer_conv2d_nl_pool conv2d_1_layer; /* Layer #1 */
AI_STATIC ai_layer_conv2d_nl_pool conv2d_3_layer; /* Layer #2 */
AI_STATIC ai_layer_conv2d_nl_pool conv2d_5_layer; /* Layer #3 */
AI_STATIC ai_layer_conv2d_nl_pool conv2d_7_layer; /* Layer #4 */
AI_STATIC ai_layer_dense dense_10_layer; /* Layer #5 */
AI_STATIC ai_layer_dense dense_11_layer; /* Layer #6 */
AI_STATIC ai_layer_dense dense_12_layer; /* Layer #7 */
AI_STATIC ai_layer_dense dense_13_layer; /* Layer #8 */
AI_STATIC ai_layer_nl dense_13_fmt_layer; /* Layer #9 */
AI_STATIC ai_layer_nl nl_14_layer; /* Layer #10 */
AI_STATIC ai_layer_nl nl_14_fmt_layer; /* Layer #11 */


/**  Array declarations section  **********************************************/
/* Array#0 */
AI_ARRAY_OBJ_DECLARE(
  conv2d_7_scratch1_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 512, AI_STATIC)

/* Array#1 */
AI_ARRAY_OBJ_DECLARE(
  conv2d_7_scratch0_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 7168, AI_STATIC)

/* Array#2 */
AI_ARRAY_OBJ_DECLARE(
  conv2d_5_scratch1_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 768, AI_STATIC)

/* Array#3 */
AI_ARRAY_OBJ_DECLARE(
  conv2d_5_scratch0_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 6144, AI_STATIC)

/* Array#4 */
AI_ARRAY_OBJ_DECLARE(
  conv2d_3_scratch1_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 928, AI_STATIC)

/* Array#5 */
AI_ARRAY_OBJ_DECLARE(
  conv2d_3_scratch0_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 2816, AI_STATIC)

/* Array#6 */
AI_ARRAY_OBJ_DECLARE(
  conv2d_1_scratch1_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 992, AI_STATIC)

/* Array#7 */
AI_ARRAY_OBJ_DECLARE(
  conv2d_1_scratch0_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 652, AI_STATIC)

/* Array#8 */
AI_ARRAY_OBJ_DECLARE(
  dense_13_bias_array, AI_ARRAY_FORMAT_S32,
  NULL, NULL, 7, AI_STATIC)

/* Array#9 */
AI_ARRAY_OBJ_DECLARE(
  dense_13_weights_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 448, AI_STATIC)

/* Array#10 */
AI_ARRAY_OBJ_DECLARE(
  dense_12_bias_array, AI_ARRAY_FORMAT_S32,
  NULL, NULL, 64, AI_STATIC)

/* Array#11 */
AI_ARRAY_OBJ_DECLARE(
  dense_12_weights_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 8192, AI_STATIC)

/* Array#12 */
AI_ARRAY_OBJ_DECLARE(
  dense_11_bias_array, AI_ARRAY_FORMAT_S32,
  NULL, NULL, 128, AI_STATIC)

/* Array#13 */
AI_ARRAY_OBJ_DECLARE(
  dense_11_weights_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 32768, AI_STATIC)

/* Array#14 */
AI_ARRAY_OBJ_DECLARE(
  dense_10_bias_array, AI_ARRAY_FORMAT_S32,
  NULL, NULL, 256, AI_STATIC)

/* Array#15 */
AI_ARRAY_OBJ_DECLARE(
  dense_10_weights_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 65536, AI_STATIC)

/* Array#16 */
AI_ARRAY_OBJ_DECLARE(
  conv2d_7_bias_array, AI_ARRAY_FORMAT_S32,
  NULL, NULL, 64, AI_STATIC)

/* Array#17 */
AI_ARRAY_OBJ_DECLARE(
  conv2d_7_weights_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 18432, AI_STATIC)

/* Array#18 */
AI_ARRAY_OBJ_DECLARE(
  conv2d_5_bias_array, AI_ARRAY_FORMAT_S32,
  NULL, NULL, 32, AI_STATIC)

/* Array#19 */
AI_ARRAY_OBJ_DECLARE(
  conv2d_5_weights_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 4608, AI_STATIC)

/* Array#20 */
AI_ARRAY_OBJ_DECLARE(
  conv2d_3_bias_array, AI_ARRAY_FORMAT_S32,
  NULL, NULL, 16, AI_STATIC)

/* Array#21 */
AI_ARRAY_OBJ_DECLARE(
  conv2d_3_weights_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 1152, AI_STATIC)

/* Array#22 */
AI_ARRAY_OBJ_DECLARE(
  conv2d_1_bias_array, AI_ARRAY_FORMAT_S32,
  NULL, NULL, 8, AI_STATIC)

/* Array#23 */
AI_ARRAY_OBJ_DECLARE(
  conv2d_1_weights_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 216, AI_STATIC)

/* Array#24 */
AI_ARRAY_OBJ_DECLARE(
  conv2d_4_input_output_array, AI_ARRAY_FORMAT_U8|AI_FMT_FLAG_IS_IO,
  NULL, NULL, 12288, AI_STATIC)

/* Array#25 */
AI_ARRAY_OBJ_DECLARE(
  conversion_0_output_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 12288, AI_STATIC)

/* Array#26 */
AI_ARRAY_OBJ_DECLARE(
  conv2d_1_output_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 7688, AI_STATIC)

/* Array#27 */
AI_ARRAY_OBJ_DECLARE(
  conv2d_3_output_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 3136, AI_STATIC)

/* Array#28 */
AI_ARRAY_OBJ_DECLARE(
  conv2d_5_output_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 1152, AI_STATIC)

/* Array#29 */
AI_ARRAY_OBJ_DECLARE(
  conv2d_7_output_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 256, AI_STATIC)

/* Array#30 */
AI_ARRAY_OBJ_DECLARE(
  dense_10_output_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 256, AI_STATIC)

/* Array#31 */
AI_ARRAY_OBJ_DECLARE(
  dense_11_output_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 128, AI_STATIC)

/* Array#32 */
AI_ARRAY_OBJ_DECLARE(
  dense_12_output_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 64, AI_STATIC)

/* Array#33 */
AI_ARRAY_OBJ_DECLARE(
  dense_13_output_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 7, AI_STATIC)

/* Array#34 */
AI_ARRAY_OBJ_DECLARE(
  dense_13_fmt_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 7, AI_STATIC)

/* Array#35 */
AI_ARRAY_OBJ_DECLARE(
  nl_14_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 7, AI_STATIC)

/* Array#36 */
AI_ARRAY_OBJ_DECLARE(
  nl_14_fmt_output_array, AI_ARRAY_FORMAT_U8|AI_FMT_FLAG_IS_IO,
  NULL, NULL, 7, AI_STATIC)

/**  Array metadata declarations section  *************************************/
/* Int quant #0 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(conv2d_7_scratch1_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.032899949699640274f),
    AI_PACK_INTQ_ZP(-128)))

/* Int quant #1 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(conv2d_5_scratch1_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.01363326981663704f),
    AI_PACK_INTQ_ZP(-128)))

/* Int quant #2 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(conv2d_3_scratch1_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.005168861243873835f),
    AI_PACK_INTQ_ZP(-128)))

/* Int quant #3 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(conv2d_1_scratch1_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.00316311395727098f),
    AI_PACK_INTQ_ZP(-128)))

/* Int quant #4 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(dense_13_bias_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.0006984500214457512f),
    AI_PACK_INTQ_ZP(0)))

/* Int quant #5 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(dense_13_weights_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.007572725880891085f),
    AI_PACK_INTQ_ZP(0)))

/* Int quant #6 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(dense_12_bias_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.0003234824107494205f),
    AI_PACK_INTQ_ZP(0)))

/* Int quant #7 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(dense_12_weights_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.0034331553615629673f),
    AI_PACK_INTQ_ZP(0)))

/* Int quant #8 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(dense_11_bias_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.0001831626723287627f),
    AI_PACK_INTQ_ZP(0)))

/* Int quant #9 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(dense_11_weights_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.0039389533922076225f),
    AI_PACK_INTQ_ZP(0)))

/* Int quant #10 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(dense_10_bias_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.00014245047350414097f),
    AI_PACK_INTQ_ZP(0)))

/* Int quant #11 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(dense_10_weights_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.004329808056354523f),
    AI_PACK_INTQ_ZP(0)))

/* Int quant #12 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(conv2d_7_bias_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 64,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(4.1319890442537144e-05f, 5.0182559789391235e-05f, 3.545544313965365e-05f, 3.058575020986609e-05f, 3.0306500775623135e-05f, 4.369304224383086e-05f, 3.6096327676204965e-05f, 3.181086867698468e-05f, 2.522498652979266e-05f, 2.294544901815243e-05f, 2.455024150549434e-05f, 1.2649344171222765e-05f, 2.8540711355162784e-05f, 2.6804920707945712e-05f, 3.583220313885249e-05f, 2.3993388822418638e-05f, 4.274093953426927e-05f, 2.3385731765301898e-05f, 3.273653783253394e-05f, 3.701903187902644e-05f, 3.904329059878364e-05f, 3.794467556872405e-05f, 4.0839255234459415e-05f, 4.225519296596758e-05f, 3.700202432810329e-05f, 3.935341737815179e-05f, 3.8258771382970735e-05f, 3.714428748935461e-05f, 4.3331125198164955e-05f, 3.8915644836379215e-05f, 3.985895455116406e-05f, 3.8290931115625426e-05f, 2.7335498089087196e-05f, 3.101078618783504e-05f, 4.780572999152355e-05f, 4.469336272450164e-05f, 3.092199403909035e-05f, 5.287773456075229e-05f, 3.6543475289363414e-05f, 2.6999961846740916e-05f, 5.3026997193228453e-05f, 2.5838844521786086e-05f, 2.37766307691345e-05f, 3.696918429341167e-05f, 3.4582262742333114e-05f, 2.5797711714403704e-05f, 3.0409200917347334e-05f, 4.923774758935906e-05f, 5.306281309458427e-05f, 4.1061452066060156e-05f, 4.048371920362115e-05f, 4.063887899974361e-05f, 3.669112629722804e-05f, 3.477982681943104e-05f, 2.576060978753958e-05f, 3.751949770958163e-05f, 3.364773147040978e-05f, 1.3527058399631642e-05f, 3.327403828734532e-05f, 3.496158751659095e-05f, 3.521902544889599e-05f, 2.825448609655723e-05f, 3.3563592296559364e-05f, 3.3634831197559834e-05f),
    AI_PACK_INTQ_ZP(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)))

/* Int quant #13 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(conv2d_7_weights_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 64,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.003030812833458185f, 0.003680889494717121f, 0.0026006558910012245f, 0.002243463881313801f, 0.002222981071099639f, 0.0032048835419118404f, 0.0026476646307855844f, 0.0023333264980465174f, 0.0018502521561458707f, 0.0016830480890348554f, 0.0018007595790550113f, 0.000927829067222774f, 0.0020934604108333588f, 0.0019661402329802513f, 0.0026282912585884333f, 0.0017599144484847784f, 0.003135046921670437f, 0.0017153428634628654f, 0.0024012241046875715f, 0.0027153450064361095f, 0.0028638243675231934f, 0.002783240983262658f, 0.0029955583158880472f, 0.0030994173139333725f, 0.002714097499847412f, 0.00288657215423882f, 0.002806280041113496f, 0.0027245325036346912f, 0.003178336890414357f, 0.0028544615488499403f, 0.0029236532282084227f, 0.002808638848364353f, 0.0020050581078976393f, 0.0022746403701603413f, 0.0035065491683781147f, 0.00327825709246099f, 0.0022681273985654116f, 0.003878580639138818f, 0.0026804630178958178f, 0.0019804465118795633f, 0.0038895290344953537f, 0.0018952785758301616f, 0.0017440152587369084f, 0.002711688634008169f, 0.002536608139052987f, 0.0018922615563496947f, 0.0022305140737444162f, 0.003611587453633547f, 0.0038921560626477003f, 0.003011856460943818f, 0.002969479886814952f, 0.0029808608815073967f, 0.0026912931352853775f, 0.002551099518314004f, 0.0018895401153713465f, 0.002752054249867797f, 0.0024680602364242077f, 0.000992209417745471f, 0.0024406497832387686f, 0.002564431633800268f, 0.0025833146646618843f, 0.0020724658388644457f, 0.0024618885945528746f, 0.0024671140126883984f),
    AI_PACK_INTQ_ZP(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)))

/* Int quant #14 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(conv2d_5_bias_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 32,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(9.823125765251461e-06f, 1.6164645785465837e-05f, 1.6287285689031705e-05f, 1.2620113011507783e-05f, 8.84780729393242e-06f, 1.5279352737707086e-05f, 1.8548211301094852e-05f, 2.00839749595616e-05f, 1.0161489626625553e-05f, 1.2130851246183738e-05f, 1.3256191778054927e-05f, 1.5807265299372375e-05f, 1.143539157055784e-05f, 9.218118066200987e-06f, 1.9560506189009175e-05f, 1.1146622455271427e-05f, 1.503685416537337e-05f, 9.443996532354504e-06f, 1.8522225218475796e-05f, 2.339136517548468e-05f, 1.3581794519268442e-05f, 9.18421119422419e-06f, 1.0286978977092076e-05f, 1.7647351342020556e-05f, 1.2073686775693204e-05f, 1.6004336430341937e-05f, 1.41704294946976e-05f, 1.292841807298828e-05f, 1.0804330486280378e-05f, 1.654115112614818e-05f, 1.1860977792821359e-05f, 1.766606692399364e-05f),
    AI_PACK_INTQ_ZP(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)))

/* Int quant #15 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(conv2d_5_weights_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 32,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.0019004428759217262f, 0.0031273127533495426f, 0.00315103936009109f, 0.0024415655061602592f, 0.00171175180003047f, 0.002956038573756814f, 0.0035884520038962364f, 0.0038855704478919506f, 0.0019659048411995173f, 0.002346909837797284f, 0.0025646251160651445f, 0.003058171831071377f, 0.0022123618982732296f, 0.0017833943711593747f, 0.0037842970341444016f, 0.0021564948838204145f, 0.0029091231990605593f, 0.0018270942382514477f, 0.003583424724638462f, 0.004525438882410526f, 0.0026276183780282736f, 0.0017768344841897488f, 0.001990182790905237f, 0.003414166159927845f, 0.0023358503822237253f, 0.0030962983146309853f, 0.002741499338299036f, 0.0025012120604515076f, 0.0020902729593217373f, 0.0032001538202166557f, 0.0022946984972804785f, 0.00341778714209795f),
    AI_PACK_INTQ_ZP(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)))

/* Int quant #16 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(conv2d_3_bias_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 16,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(1.004201294563245e-05f, 1.5371653717011213e-05f, 7.405614724120824e-06f, 2.6448291464475915e-05f, 1.0387610927864444e-05f, 1.374957719235681e-05f, 1.7748941900208592e-05f, 1.5058956705615856e-05f, 1.2490254448493943e-05f, 1.6801301171653904e-05f, 1.1724884643626865e-05f, 1.0503023986530025e-05f, 1.1987487596343271e-05f, 6.903099802002544e-06f, 1.3742838746111374e-05f, 1.617568159417715e-05f),
    AI_PACK_INTQ_ZP(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)))

/* Int quant #17 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(conv2d_3_weights_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 16,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.0031747238244861364f, 0.004859658423811197f, 0.0023412418086081743f, 0.008361472748219967f, 0.0032839826308190823f, 0.004346848465502262f, 0.005611224099993706f, 0.004760801326483488f, 0.00394872110337019f, 0.0053116329945623875f, 0.003706753719598055f, 0.003320469753816724f, 0.003789774142205715f, 0.002182374708354473f, 0.004344718065112829f, 0.005113847088068724f),
    AI_PACK_INTQ_ZP(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)))

/* Int quant #18 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(conv2d_1_bias_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 8,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(8.868228178471327e-06f, 8.001256901479792e-06f, 8.25306233309675e-06f, 8.937000529840589e-06f, 9.576698175806087e-06f, 9.316016985394526e-06f, 9.146996490017045e-06f, 1.1331527275615372e-05f),
    AI_PACK_INTQ_ZP(0, 0, 0, 0, 0, 0, 0, 0)))

/* Int quant #19 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(conv2d_1_weights_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 8,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.0022613981273025274f, 0.002040320308879018f, 0.0021045308094471693f, 0.002278934931382537f, 0.002442057942971587f, 0.0023755840957164764f, 0.002332483883947134f, 0.002889539347961545f),
    AI_PACK_INTQ_ZP(0, 0, 0, 0, 0, 0, 0, 0)))

/* Int quant #20 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(conv2d_4_input_output_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_U8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.003921568859368563f),
    AI_PACK_UINTQ_ZP(0)))

/* Int quant #21 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(conversion_0_output_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.003921568859368563f),
    AI_PACK_INTQ_ZP(-128)))

/* Int quant #22 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(conv2d_1_output_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.00316311395727098f),
    AI_PACK_INTQ_ZP(-128)))

/* Int quant #23 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(conv2d_3_output_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.005168861243873835f),
    AI_PACK_INTQ_ZP(-128)))

/* Int quant #24 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(conv2d_5_output_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.01363326981663704f),
    AI_PACK_INTQ_ZP(-128)))

/* Int quant #25 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(conv2d_7_output_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.032899949699640274f),
    AI_PACK_INTQ_ZP(-128)))

/* Int quant #26 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(dense_10_output_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.04650034010410309f),
    AI_PACK_INTQ_ZP(-128)))

/* Int quant #27 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(dense_11_output_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.09422305971384048f),
    AI_PACK_INTQ_ZP(-128)))

/* Int quant #28 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(dense_12_output_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.09223230928182602f),
    AI_PACK_INTQ_ZP(-128)))

/* Int quant #29 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(dense_13_output_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.40353232622146606f),
    AI_PACK_INTQ_ZP(-8)))

/* Int quant #30 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(nl_14_fmt_output_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_U8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.00390625f),
    AI_PACK_UINTQ_ZP(0)))

/**  Tensor declarations section  *********************************************/
/* Tensor #0 */
AI_TENSOR_OBJ_DECLARE(
  conv2d_7_scratch1, AI_STATIC,
  0x0, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 4, 2), AI_STRIDE_INIT(4, 1, 1, 64, 256),
  1, &conv2d_7_scratch1_array, &conv2d_7_scratch1_intq)

/* Tensor #1 */
AI_TENSOR_OBJ_DECLARE(
  conv2d_7_scratch0, AI_STATIC,
  0x0, 0x0,
  AI_SHAPE_INIT(4, 1, 7168, 1, 1), AI_STRIDE_INIT(4, 1, 1, 7168, 7168),
  1, &conv2d_7_scratch0_array, NULL)

/* Tensor #2 */
AI_TENSOR_OBJ_DECLARE(
  conv2d_5_scratch1, AI_STATIC,
  0x0, 0x0,
  AI_SHAPE_INIT(4, 1, 32, 12, 2), AI_STRIDE_INIT(4, 1, 1, 32, 384),
  1, &conv2d_5_scratch1_array, &conv2d_5_scratch1_intq)

/* Tensor #3 */
AI_TENSOR_OBJ_DECLARE(
  conv2d_5_scratch0, AI_STATIC,
  0x0, 0x0,
  AI_SHAPE_INIT(4, 1, 6144, 1, 1), AI_STRIDE_INIT(4, 1, 1, 6144, 6144),
  1, &conv2d_5_scratch0_array, NULL)

/* Tensor #4 */
AI_TENSOR_OBJ_DECLARE(
  conv2d_3_scratch1, AI_STATIC,
  0x0, 0x0,
  AI_SHAPE_INIT(4, 1, 16, 29, 2), AI_STRIDE_INIT(4, 1, 1, 16, 464),
  1, &conv2d_3_scratch1_array, &conv2d_3_scratch1_intq)

/* Tensor #5 */
AI_TENSOR_OBJ_DECLARE(
  conv2d_3_scratch0, AI_STATIC,
  0x0, 0x0,
  AI_SHAPE_INIT(4, 1, 2816, 1, 1), AI_STRIDE_INIT(4, 1, 1, 2816, 2816),
  1, &conv2d_3_scratch0_array, NULL)

/* Tensor #6 */
AI_TENSOR_OBJ_DECLARE(
  conv2d_1_scratch1, AI_STATIC,
  0x0, 0x0,
  AI_SHAPE_INIT(4, 1, 8, 62, 2), AI_STRIDE_INIT(4, 1, 1, 8, 496),
  1, &conv2d_1_scratch1_array, &conv2d_1_scratch1_intq)

/* Tensor #7 */
AI_TENSOR_OBJ_DECLARE(
  conv2d_1_scratch0, AI_STATIC,
  0x0, 0x0,
  AI_SHAPE_INIT(4, 1, 652, 1, 1), AI_STRIDE_INIT(4, 1, 1, 652, 652),
  1, &conv2d_1_scratch0_array, NULL)

/* Tensor #8 */
AI_TENSOR_OBJ_DECLARE(
  dense_13_bias, AI_STATIC,
  0x0, 0x0,
  AI_SHAPE_INIT(4, 1, 7, 1, 1), AI_STRIDE_INIT(4, 4, 4, 28, 28),
  1, &dense_13_bias_array, &dense_13_bias_intq)

/* Tensor #9 */
AI_TENSOR_OBJ_DECLARE(
  dense_13_weights, AI_STATIC,
  0x0, 0x0,
  AI_SHAPE_INIT(4, 64, 7, 1, 1), AI_STRIDE_INIT(4, 1, 64, 448, 448),
  1, &dense_13_weights_array, &dense_13_weights_intq)

/* Tensor #10 */
AI_TENSOR_OBJ_DECLARE(
  dense_12_bias, AI_STATIC,
  0x0, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 1, 1), AI_STRIDE_INIT(4, 4, 4, 256, 256),
  1, &dense_12_bias_array, &dense_12_bias_intq)

/* Tensor #11 */
AI_TENSOR_OBJ_DECLARE(
  dense_12_weights, AI_STATIC,
  0x0, 0x0,
  AI_SHAPE_INIT(4, 128, 64, 1, 1), AI_STRIDE_INIT(4, 1, 128, 8192, 8192),
  1, &dense_12_weights_array, &dense_12_weights_intq)

/* Tensor #12 */
AI_TENSOR_OBJ_DECLARE(
  dense_11_bias, AI_STATIC,
  0x0, 0x0,
  AI_SHAPE_INIT(4, 1, 128, 1, 1), AI_STRIDE_INIT(4, 4, 4, 512, 512),
  1, &dense_11_bias_array, &dense_11_bias_intq)

/* Tensor #13 */
AI_TENSOR_OBJ_DECLARE(
  dense_11_weights, AI_STATIC,
  0x0, 0x0,
  AI_SHAPE_INIT(4, 256, 128, 1, 1), AI_STRIDE_INIT(4, 1, 256, 32768, 32768),
  1, &dense_11_weights_array, &dense_11_weights_intq)

/* Tensor #14 */
AI_TENSOR_OBJ_DECLARE(
  dense_10_bias, AI_STATIC,
  0x0, 0x0,
  AI_SHAPE_INIT(4, 1, 256, 1, 1), AI_STRIDE_INIT(4, 4, 4, 1024, 1024),
  1, &dense_10_bias_array, &dense_10_bias_intq)

/* Tensor #15 */
AI_TENSOR_OBJ_DECLARE(
  dense_10_weights, AI_STATIC,
  0x0, 0x0,
  AI_SHAPE_INIT(4, 256, 256, 1, 1), AI_STRIDE_INIT(4, 1, 256, 65536, 65536),
  1, &dense_10_weights_array, &dense_10_weights_intq)

/* Tensor #16 */
AI_TENSOR_OBJ_DECLARE(
  conv2d_7_bias, AI_STATIC,
  0x0, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 1, 1), AI_STRIDE_INIT(4, 4, 4, 256, 256),
  1, &conv2d_7_bias_array, &conv2d_7_bias_intq)

/* Tensor #17 */
AI_TENSOR_OBJ_DECLARE(
  conv2d_7_weights, AI_STATIC,
  0x0, 0x0,
  AI_SHAPE_INIT(4, 32, 3, 3, 64), AI_STRIDE_INIT(4, 1, 32, 96, 288),
  1, &conv2d_7_weights_array, &conv2d_7_weights_intq)

/* Tensor #18 */
AI_TENSOR_OBJ_DECLARE(
  conv2d_5_bias, AI_STATIC,
  0x0, 0x0,
  AI_SHAPE_INIT(4, 1, 32, 1, 1), AI_STRIDE_INIT(4, 4, 4, 128, 128),
  1, &conv2d_5_bias_array, &conv2d_5_bias_intq)

/* Tensor #19 */
AI_TENSOR_OBJ_DECLARE(
  conv2d_5_weights, AI_STATIC,
  0x0, 0x0,
  AI_SHAPE_INIT(4, 16, 3, 3, 32), AI_STRIDE_INIT(4, 1, 16, 48, 144),
  1, &conv2d_5_weights_array, &conv2d_5_weights_intq)

/* Tensor #20 */
AI_TENSOR_OBJ_DECLARE(
  conv2d_3_bias, AI_STATIC,
  0x0, 0x0,
  AI_SHAPE_INIT(4, 1, 16, 1, 1), AI_STRIDE_INIT(4, 4, 4, 64, 64),
  1, &conv2d_3_bias_array, &conv2d_3_bias_intq)

/* Tensor #21 */
AI_TENSOR_OBJ_DECLARE(
  conv2d_3_weights, AI_STATIC,
  0x0, 0x0,
  AI_SHAPE_INIT(4, 8, 3, 3, 16), AI_STRIDE_INIT(4, 1, 8, 24, 72),
  1, &conv2d_3_weights_array, &conv2d_3_weights_intq)

/* Tensor #22 */
AI_TENSOR_OBJ_DECLARE(
  conv2d_1_bias, AI_STATIC,
  0x0, 0x0,
  AI_SHAPE_INIT(4, 1, 8, 1, 1), AI_STRIDE_INIT(4, 4, 4, 32, 32),
  1, &conv2d_1_bias_array, &conv2d_1_bias_intq)

/* Tensor #23 */
AI_TENSOR_OBJ_DECLARE(
  conv2d_1_weights, AI_STATIC,
  0x0, 0x0,
  AI_SHAPE_INIT(4, 3, 3, 3, 8), AI_STRIDE_INIT(4, 1, 3, 9, 27),
  1, &conv2d_1_weights_array, &conv2d_1_weights_intq)

/* Tensor #24 */
AI_TENSOR_OBJ_DECLARE(
  conv2d_4_input_output, AI_STATIC,
  0x0, 0x0,
  AI_SHAPE_INIT(4, 1, 3, 64, 64), AI_STRIDE_INIT(4, 1, 1, 3, 192),
  1, &conv2d_4_input_output_array, &conv2d_4_input_output_intq)

/* Tensor #25 */
AI_TENSOR_OBJ_DECLARE(
  conversion_0_output, AI_STATIC,
  0x0, 0x0,
  AI_SHAPE_INIT(4, 1, 3, 64, 64), AI_STRIDE_INIT(4, 1, 1, 3, 192),
  1, &conversion_0_output_array, &conversion_0_output_intq)

/* Tensor #26 */
AI_TENSOR_OBJ_DECLARE(
  conv2d_1_output, AI_STATIC,
  0x0, 0x0,
  AI_SHAPE_INIT(4, 1, 8, 31, 31), AI_STRIDE_INIT(4, 1, 1, 8, 248),
  1, &conv2d_1_output_array, &conv2d_1_output_intq)

/* Tensor #27 */
AI_TENSOR_OBJ_DECLARE(
  conv2d_3_output, AI_STATIC,
  0x0, 0x0,
  AI_SHAPE_INIT(4, 1, 16, 14, 14), AI_STRIDE_INIT(4, 1, 1, 16, 224),
  1, &conv2d_3_output_array, &conv2d_3_output_intq)

/* Tensor #28 */
AI_TENSOR_OBJ_DECLARE(
  conv2d_5_output, AI_STATIC,
  0x0, 0x0,
  AI_SHAPE_INIT(4, 1, 32, 6, 6), AI_STRIDE_INIT(4, 1, 1, 32, 192),
  1, &conv2d_5_output_array, &conv2d_5_output_intq)

/* Tensor #29 */
AI_TENSOR_OBJ_DECLARE(
  conv2d_7_output, AI_STATIC,
  0x0, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 2, 2), AI_STRIDE_INIT(4, 1, 1, 64, 128),
  1, &conv2d_7_output_array, &conv2d_7_output_intq)

/* Tensor #30 */
AI_TENSOR_OBJ_DECLARE(
  conv2d_7_output0, AI_STATIC,
  0x0, 0x0,
  AI_SHAPE_INIT(4, 1, 256, 1, 1), AI_STRIDE_INIT(4, 1, 1, 256, 256),
  1, &conv2d_7_output_array, &conv2d_7_output_intq)

/* Tensor #31 */
AI_TENSOR_OBJ_DECLARE(
  dense_10_output, AI_STATIC,
  0x0, 0x0,
  AI_SHAPE_INIT(4, 1, 256, 1, 1), AI_STRIDE_INIT(4, 1, 1, 256, 256),
  1, &dense_10_output_array, &dense_10_output_intq)

/* Tensor #32 */
AI_TENSOR_OBJ_DECLARE(
  dense_11_output, AI_STATIC,
  0x0, 0x0,
  AI_SHAPE_INIT(4, 1, 128, 1, 1), AI_STRIDE_INIT(4, 1, 1, 128, 128),
  1, &dense_11_output_array, &dense_11_output_intq)

/* Tensor #33 */
AI_TENSOR_OBJ_DECLARE(
  dense_12_output, AI_STATIC,
  0x0, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 1, 1), AI_STRIDE_INIT(4, 1, 1, 64, 64),
  1, &dense_12_output_array, &dense_12_output_intq)

/* Tensor #34 */
AI_TENSOR_OBJ_DECLARE(
  dense_13_output, AI_STATIC,
  0x0, 0x0,
  AI_SHAPE_INIT(4, 1, 7, 1, 1), AI_STRIDE_INIT(4, 1, 1, 7, 7),
  1, &dense_13_output_array, &dense_13_output_intq)

/* Tensor #35 */
AI_TENSOR_OBJ_DECLARE(
  dense_13_fmt_output, AI_STATIC,
  0x0, 0x0,
  AI_SHAPE_INIT(4, 1, 7, 1, 1), AI_STRIDE_INIT(4, 4, 4, 28, 28),
  1, &dense_13_fmt_output_array, NULL)

/* Tensor #36 */
AI_TENSOR_OBJ_DECLARE(
  nl_14_output, AI_STATIC,
  0x0, 0x0,
  AI_SHAPE_INIT(4, 1, 7, 1, 1), AI_STRIDE_INIT(4, 4, 4, 28, 28),
  1, &nl_14_output_array, NULL)

/* Tensor #37 */
AI_TENSOR_OBJ_DECLARE(
  nl_14_fmt_output, AI_STATIC,
  0x0, 0x0,
  AI_SHAPE_INIT(4, 1, 7, 1, 1), AI_STRIDE_INIT(4, 1, 1, 7, 7),
  1, &nl_14_fmt_output_array, &nl_14_fmt_output_intq)



/**  Layer declarations section  **********************************************/


AI_TENSOR_CHAIN_OBJ_DECLARE(
  conversion_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conv2d_4_input_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conversion_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  conversion_0_layer, 0,
  NL_TYPE,
  nl, node_convert_integer,
  &AI_NET_OBJ_INSTANCE, &conv2d_1_layer, AI_STATIC,
  .tensors = &conversion_0_chain, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  conv2d_1_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conversion_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conv2d_1_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &conv2d_1_weights, &conv2d_1_bias, NULL),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &conv2d_1_scratch0, &conv2d_1_scratch1)
)

AI_LAYER_OBJ_DECLARE(
  conv2d_1_layer, 1,
  OPTIMIZED_CONV2D_TYPE,
  conv2d_nl_pool, forward_conv2d_nl_pool_integer_SSSA_ch,
  &AI_NET_OBJ_INSTANCE, &conv2d_3_layer, AI_STATIC,
  .tensors = &conv2d_1_chain, 
  .groups = 1, 
  .nl_func = NULL, 
  .filter_stride = AI_SHAPE_2D_INIT(1, 1), 
  .dilation = AI_SHAPE_2D_INIT(1, 1), 
  .filter_pad = AI_SHAPE_INIT(4, 0, 0, 0, 0), 
  .pool_size = AI_SHAPE_2D_INIT(2, 2), 
  .pool_stride = AI_SHAPE_2D_INIT(2, 2), 
  .pool_pad = AI_SHAPE_INIT(4, 0, 0, 0, 0), 
  .pool_func = pool_func_ap_array_integer_INT8, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  conv2d_3_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conv2d_1_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conv2d_3_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &conv2d_3_weights, &conv2d_3_bias, NULL),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &conv2d_3_scratch0, &conv2d_3_scratch1)
)

AI_LAYER_OBJ_DECLARE(
  conv2d_3_layer, 3,
  OPTIMIZED_CONV2D_TYPE,
  conv2d_nl_pool, forward_conv2d_nl_pool_integer_SSSA_ch,
  &AI_NET_OBJ_INSTANCE, &conv2d_5_layer, AI_STATIC,
  .tensors = &conv2d_3_chain, 
  .groups = 1, 
  .nl_func = NULL, 
  .filter_stride = AI_SHAPE_2D_INIT(1, 1), 
  .dilation = AI_SHAPE_2D_INIT(1, 1), 
  .filter_pad = AI_SHAPE_INIT(4, 0, 0, 0, 0), 
  .pool_size = AI_SHAPE_2D_INIT(2, 2), 
  .pool_stride = AI_SHAPE_2D_INIT(2, 2), 
  .pool_pad = AI_SHAPE_INIT(4, 0, 0, 0, 0), 
  .pool_func = pool_func_ap_array_integer_INT8, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  conv2d_5_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conv2d_3_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conv2d_5_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &conv2d_5_weights, &conv2d_5_bias, NULL),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &conv2d_5_scratch0, &conv2d_5_scratch1)
)

AI_LAYER_OBJ_DECLARE(
  conv2d_5_layer, 5,
  OPTIMIZED_CONV2D_TYPE,
  conv2d_nl_pool, forward_conv2d_nl_pool_integer_SSSA_ch,
  &AI_NET_OBJ_INSTANCE, &conv2d_7_layer, AI_STATIC,
  .tensors = &conv2d_5_chain, 
  .groups = 1, 
  .nl_func = NULL, 
  .filter_stride = AI_SHAPE_2D_INIT(1, 1), 
  .dilation = AI_SHAPE_2D_INIT(1, 1), 
  .filter_pad = AI_SHAPE_INIT(4, 0, 0, 0, 0), 
  .pool_size = AI_SHAPE_2D_INIT(2, 2), 
  .pool_stride = AI_SHAPE_2D_INIT(2, 2), 
  .pool_pad = AI_SHAPE_INIT(4, 0, 0, 0, 0), 
  .pool_func = pool_func_ap_array_integer_INT8, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  conv2d_7_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conv2d_5_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conv2d_7_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &conv2d_7_weights, &conv2d_7_bias, NULL),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &conv2d_7_scratch0, &conv2d_7_scratch1)
)

AI_LAYER_OBJ_DECLARE(
  conv2d_7_layer, 7,
  OPTIMIZED_CONV2D_TYPE,
  conv2d_nl_pool, forward_conv2d_nl_pool_integer_SSSA_ch,
  &AI_NET_OBJ_INSTANCE, &dense_10_layer, AI_STATIC,
  .tensors = &conv2d_7_chain, 
  .groups = 1, 
  .nl_func = NULL, 
  .filter_stride = AI_SHAPE_2D_INIT(1, 1), 
  .dilation = AI_SHAPE_2D_INIT(1, 1), 
  .filter_pad = AI_SHAPE_INIT(4, 0, 0, 0, 0), 
  .pool_size = AI_SHAPE_2D_INIT(2, 2), 
  .pool_stride = AI_SHAPE_2D_INIT(2, 2), 
  .pool_pad = AI_SHAPE_INIT(4, 0, 0, 0, 0), 
  .pool_func = pool_func_ap_array_integer_INT8, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  dense_10_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conv2d_7_output0),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &dense_10_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &dense_10_weights, &dense_10_bias),
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  dense_10_layer, 10,
  DENSE_TYPE,
  dense, forward_dense_integer_SSSA,
  &AI_NET_OBJ_INSTANCE, &dense_11_layer, AI_STATIC,
  .tensors = &dense_10_chain, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  dense_11_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &dense_10_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &dense_11_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &dense_11_weights, &dense_11_bias),
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  dense_11_layer, 11,
  DENSE_TYPE,
  dense, forward_dense_integer_SSSA,
  &AI_NET_OBJ_INSTANCE, &dense_12_layer, AI_STATIC,
  .tensors = &dense_11_chain, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  dense_12_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &dense_11_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &dense_12_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &dense_12_weights, &dense_12_bias),
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  dense_12_layer, 12,
  DENSE_TYPE,
  dense, forward_dense_integer_SSSA,
  &AI_NET_OBJ_INSTANCE, &dense_13_layer, AI_STATIC,
  .tensors = &dense_12_chain, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  dense_13_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &dense_12_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &dense_13_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &dense_13_weights, &dense_13_bias),
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  dense_13_layer, 13,
  DENSE_TYPE,
  dense, forward_dense_integer_SSSA,
  &AI_NET_OBJ_INSTANCE, &dense_13_fmt_layer, AI_STATIC,
  .tensors = &dense_13_chain, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  dense_13_fmt_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &dense_13_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &dense_13_fmt_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  dense_13_fmt_layer, 13,
  NL_TYPE,
  nl, node_convert,
  &AI_NET_OBJ_INSTANCE, &nl_14_layer, AI_STATIC,
  .tensors = &dense_13_fmt_chain, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  nl_14_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &dense_13_fmt_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &nl_14_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  nl_14_layer, 14,
  NL_TYPE,
  nl, forward_sm,
  &AI_NET_OBJ_INSTANCE, &nl_14_fmt_layer, AI_STATIC,
  .tensors = &nl_14_chain, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  nl_14_fmt_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &nl_14_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &nl_14_fmt_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  nl_14_fmt_layer, 14,
  NL_TYPE,
  nl, node_convert,
  &AI_NET_OBJ_INSTANCE, &nl_14_fmt_layer, AI_STATIC,
  .tensors = &nl_14_fmt_chain, 
)


AI_NETWORK_OBJ_DECLARE(
  AI_NET_OBJ_INSTANCE, AI_STATIC,
  AI_BUFFER_OBJ_INIT(AI_BUFFER_FORMAT_U8,
                     1, 1, 133652, 1,
                     NULL),
  AI_BUFFER_OBJ_INIT(AI_BUFFER_FORMAT_U8,
                     1, 1, 14428, 1,
                     NULL),
  AI_TENSOR_LIST_IO_OBJ_INIT(AI_FLAG_NONE, AI_NETWORK_IN_NUM, &conv2d_4_input_output),
  AI_TENSOR_LIST_IO_OBJ_INIT(AI_FLAG_NONE, AI_NETWORK_OUT_NUM, &nl_14_fmt_output),
  &conversion_0_layer, 0, NULL)



AI_DECLARE_STATIC
ai_bool network_configure_activations(
  ai_network* net_ctx, const ai_buffer* activation_buffer)
{
  AI_ASSERT(net_ctx &&  activation_buffer && activation_buffer->data)

  ai_ptr activations = AI_PTR(AI_PTR_ALIGN(activation_buffer->data, AI_NETWORK_ACTIVATIONS_ALIGNMENT));
  AI_ASSERT(activations)
  AI_UNUSED(net_ctx)

  {
    /* Updating activations (byte) offsets */
    conv2d_7_scratch1_array.data = AI_PTR(activations + 7168);
    conv2d_7_scratch1_array.data_start = AI_PTR(activations + 7168);
    conv2d_7_scratch0_array.data = AI_PTR(activations + 0);
    conv2d_7_scratch0_array.data_start = AI_PTR(activations + 0);
    conv2d_5_scratch1_array.data = AI_PTR(activations + 9280);
    conv2d_5_scratch1_array.data_start = AI_PTR(activations + 9280);
    conv2d_5_scratch0_array.data = AI_PTR(activations + 3136);
    conv2d_5_scratch0_array.data_start = AI_PTR(activations + 3136);
    conv2d_3_scratch1_array.data = AI_PTR(activations + 10744);
    conv2d_3_scratch1_array.data_start = AI_PTR(activations + 10744);
    conv2d_3_scratch0_array.data = AI_PTR(activations + 7928);
    conv2d_3_scratch0_array.data_start = AI_PTR(activations + 7928);
    conv2d_1_scratch1_array.data = AI_PTR(activations + 13436);
    conv2d_1_scratch1_array.data_start = AI_PTR(activations + 13436);
    conv2d_1_scratch0_array.data = AI_PTR(activations + 12784);
    conv2d_1_scratch0_array.data_start = AI_PTR(activations + 12784);
    conv2d_4_input_output_array.data = AI_PTR(NULL);
    conv2d_4_input_output_array.data_start = AI_PTR(NULL);
    conversion_0_output_array.data = AI_PTR(activations + 496);
    conversion_0_output_array.data_start = AI_PTR(activations + 496);
    conv2d_1_output_array.data = AI_PTR(activations + 240);
    conv2d_1_output_array.data_start = AI_PTR(activations + 240);
    conv2d_3_output_array.data = AI_PTR(activations + 0);
    conv2d_3_output_array.data_start = AI_PTR(activations + 0);
    conv2d_5_output_array.data = AI_PTR(activations + 10048);
    conv2d_5_output_array.data_start = AI_PTR(activations + 10048);
    conv2d_7_output_array.data = AI_PTR(activations + 7680);
    conv2d_7_output_array.data_start = AI_PTR(activations + 7680);
    dense_10_output_array.data = AI_PTR(activations + 0);
    dense_10_output_array.data_start = AI_PTR(activations + 0);
    dense_11_output_array.data = AI_PTR(activations + 256);
    dense_11_output_array.data_start = AI_PTR(activations + 256);
    dense_12_output_array.data = AI_PTR(activations + 0);
    dense_12_output_array.data_start = AI_PTR(activations + 0);
    dense_13_output_array.data = AI_PTR(activations + 64);
    dense_13_output_array.data_start = AI_PTR(activations + 64);
    dense_13_fmt_output_array.data = AI_PTR(activations + 0);
    dense_13_fmt_output_array.data_start = AI_PTR(activations + 0);
    nl_14_output_array.data = AI_PTR(activations + 28);
    nl_14_output_array.data_start = AI_PTR(activations + 28);
    nl_14_fmt_output_array.data = AI_PTR(NULL);
    nl_14_fmt_output_array.data_start = AI_PTR(NULL);
    
  }
  return true;
}



AI_DECLARE_STATIC
ai_bool network_configure_weights(
  ai_network* net_ctx, const ai_buffer* weights_buffer)
{
  AI_ASSERT(net_ctx &&  weights_buffer && weights_buffer->data)

  ai_ptr weights = AI_PTR(weights_buffer->data);
  AI_ASSERT(weights)
  AI_UNUSED(net_ctx)

  {
    /* Updating weights (byte) offsets */
    
    dense_13_bias_array.format |= AI_FMT_FLAG_CONST;
    dense_13_bias_array.data = AI_PTR(weights + 133624);
    dense_13_bias_array.data_start = AI_PTR(weights + 133624);
    dense_13_weights_array.format |= AI_FMT_FLAG_CONST;
    dense_13_weights_array.data = AI_PTR(weights + 133176);
    dense_13_weights_array.data_start = AI_PTR(weights + 133176);
    dense_12_bias_array.format |= AI_FMT_FLAG_CONST;
    dense_12_bias_array.data = AI_PTR(weights + 132920);
    dense_12_bias_array.data_start = AI_PTR(weights + 132920);
    dense_12_weights_array.format |= AI_FMT_FLAG_CONST;
    dense_12_weights_array.data = AI_PTR(weights + 124728);
    dense_12_weights_array.data_start = AI_PTR(weights + 124728);
    dense_11_bias_array.format |= AI_FMT_FLAG_CONST;
    dense_11_bias_array.data = AI_PTR(weights + 124216);
    dense_11_bias_array.data_start = AI_PTR(weights + 124216);
    dense_11_weights_array.format |= AI_FMT_FLAG_CONST;
    dense_11_weights_array.data = AI_PTR(weights + 91448);
    dense_11_weights_array.data_start = AI_PTR(weights + 91448);
    dense_10_bias_array.format |= AI_FMT_FLAG_CONST;
    dense_10_bias_array.data = AI_PTR(weights + 90424);
    dense_10_bias_array.data_start = AI_PTR(weights + 90424);
    dense_10_weights_array.format |= AI_FMT_FLAG_CONST;
    dense_10_weights_array.data = AI_PTR(weights + 24888);
    dense_10_weights_array.data_start = AI_PTR(weights + 24888);
    conv2d_7_bias_array.format |= AI_FMT_FLAG_CONST;
    conv2d_7_bias_array.data = AI_PTR(weights + 24632);
    conv2d_7_bias_array.data_start = AI_PTR(weights + 24632);
    conv2d_7_weights_array.format |= AI_FMT_FLAG_CONST;
    conv2d_7_weights_array.data = AI_PTR(weights + 6200);
    conv2d_7_weights_array.data_start = AI_PTR(weights + 6200);
    conv2d_5_bias_array.format |= AI_FMT_FLAG_CONST;
    conv2d_5_bias_array.data = AI_PTR(weights + 6072);
    conv2d_5_bias_array.data_start = AI_PTR(weights + 6072);
    conv2d_5_weights_array.format |= AI_FMT_FLAG_CONST;
    conv2d_5_weights_array.data = AI_PTR(weights + 1464);
    conv2d_5_weights_array.data_start = AI_PTR(weights + 1464);
    conv2d_3_bias_array.format |= AI_FMT_FLAG_CONST;
    conv2d_3_bias_array.data = AI_PTR(weights + 1400);
    conv2d_3_bias_array.data_start = AI_PTR(weights + 1400);
    conv2d_3_weights_array.format |= AI_FMT_FLAG_CONST;
    conv2d_3_weights_array.data = AI_PTR(weights + 248);
    conv2d_3_weights_array.data_start = AI_PTR(weights + 248);
    conv2d_1_bias_array.format |= AI_FMT_FLAG_CONST;
    conv2d_1_bias_array.data = AI_PTR(weights + 216);
    conv2d_1_bias_array.data_start = AI_PTR(weights + 216);
    conv2d_1_weights_array.format |= AI_FMT_FLAG_CONST;
    conv2d_1_weights_array.data = AI_PTR(weights + 0);
    conv2d_1_weights_array.data_start = AI_PTR(weights + 0);
  }

  return true;
}


/**  PUBLIC APIs SECTION  *****************************************************/

AI_API_ENTRY
ai_bool ai_network_get_info(
  ai_handle network, ai_network_report* report)
{
  ai_network* net_ctx = AI_NETWORK_ACQUIRE_CTX(network);

  if ( report && net_ctx )
  {
    ai_network_report r = {
      .model_name        = AI_NETWORK_MODEL_NAME,
      .model_signature   = AI_NETWORK_MODEL_SIGNATURE,
      .model_datetime    = AI_TOOLS_DATE_TIME,
      
      .compile_datetime  = AI_TOOLS_COMPILE_TIME,
      
      .runtime_revision  = ai_platform_runtime_get_revision(),
      .runtime_version   = ai_platform_runtime_get_version(),

      .tool_revision     = AI_TOOLS_REVISION_ID,
      .tool_version      = {AI_TOOLS_VERSION_MAJOR, AI_TOOLS_VERSION_MINOR,
                            AI_TOOLS_VERSION_MICRO, 0x0},
      .tool_api_version  = {AI_TOOLS_API_VERSION_MAJOR, AI_TOOLS_API_VERSION_MINOR,
                            AI_TOOLS_API_VERSION_MICRO, 0x0},

      .api_version            = ai_platform_api_get_version(),
      .interface_api_version  = ai_platform_interface_api_get_version(),
      
      .n_macc            = 2938301,
      .n_inputs          = 0,
      .inputs            = NULL,
      .n_outputs         = 0,
      .outputs           = NULL,
      .activations       = AI_STRUCT_INIT,
      .params            = AI_STRUCT_INIT,
      .n_nodes           = 0,
      .signature         = 0x0,
    };

    if ( !ai_platform_api_get_network_report(network, &r) ) return false;

    *report = r;
    return true;
  }

  return false;
}

AI_API_ENTRY
ai_error ai_network_get_error(ai_handle network)
{
  return ai_platform_network_get_error(network);
}

AI_API_ENTRY
ai_error ai_network_create(
  ai_handle* network, const ai_buffer* network_config)
{
  return ai_platform_network_create(
    network, network_config, 
    &AI_NET_OBJ_INSTANCE,
    AI_TOOLS_API_VERSION_MAJOR, AI_TOOLS_API_VERSION_MINOR, AI_TOOLS_API_VERSION_MICRO);
}

AI_API_ENTRY
ai_handle ai_network_destroy(ai_handle network)
{
  return ai_platform_network_destroy(network);
}

AI_API_ENTRY
ai_bool ai_network_init(
  ai_handle network, const ai_network_params* params)
{
  ai_network* net_ctx = ai_platform_network_init(network, params);
  if ( !net_ctx ) return false;

  ai_bool ok = true;
  ok &= network_configure_weights(net_ctx, &params->params);
  ok &= network_configure_activations(net_ctx, &params->activations);

  ok &= ai_platform_network_post_init(network);

  return ok;
}


AI_API_ENTRY
ai_i32 ai_network_run(
  ai_handle network, const ai_buffer* input, ai_buffer* output)
{
  return ai_platform_network_process(network, input, output);
}

AI_API_ENTRY
ai_i32 ai_network_forward(ai_handle network, const ai_buffer* input)
{
  return ai_platform_network_process(network, input, NULL);
}




#undef AI_NETWORK_MODEL_SIGNATURE
#undef AI_NET_OBJ_INSTANCE
#undef AI_TOOLS_VERSION_MAJOR
#undef AI_TOOLS_VERSION_MINOR
#undef AI_TOOLS_VERSION_MICRO
#undef AI_TOOLS_API_VERSION_MAJOR
#undef AI_TOOLS_API_VERSION_MINOR
#undef AI_TOOLS_API_VERSION_MICRO
#undef AI_TOOLS_DATE_TIME
#undef AI_TOOLS_COMPILE_TIME

