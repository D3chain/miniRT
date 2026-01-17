/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flt_constants.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fox <fox@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 12:39:27 by fox               #+#    #+#             */
/*   Updated: 2026/01/17 12:41:16 by fox              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FLOAT_CONSTANTS_H
# define FLOAT_CONSTANTS_H

# ifdef USE_DBL_NUMBER
#  define FLT_TYPE double

#  define FLT_0    0.0
#  define FLT_1    1.0
#  define FLT_2    2.0
#  define FLT_3    3.0
#  define FLT_4    4.0
#  define FLT_5    5.0
#  define FLT_6    6.0
#  define FLT_7    7.0
#  define FLT_8    8.0
#  define FLT_9    9.0
#  define FLT_10   10.0
#  define FLT_11   11.0
#  define FLT_12   12.0
#  define FLT_13   13.0
#  define FLT_14   14.0
#  define FLT_15   15.0
#  define FLT_16   16.0
#  define FLT_17   17.0
#  define FLT_18   18.0
#  define FLT_19   19.0
#  define FLT_20   20.0
#  define FLT_21   21.0
#  define FLT_22   22.0
#  define FLT_23   23.0
#  define FLT_24   24.0
#  define FLT_25   25.0
#  define FLT_26   26.0
#  define FLT_27   27.0
#  define FLT_28   28.0
#  define FLT_29   29.0
#  define FLT_30   30.0
#  define FLT_31   31.0
#  define FLT_32   32.0
#  define FLT_33   33.0
#  define FLT_34   34.0
#  define FLT_35   35.0
#  define FLT_36   36.0
#  define FLT_37   37.0
#  define FLT_38   38.0
#  define FLT_39   39.0
#  define FLT_40   40.0
#  define FLT_41   41.0
#  define FLT_42   42.0
#  define FLT_43   43.0
#  define FLT_44   44.0
#  define FLT_45   45.0
#  define FLT_46   46.0
#  define FLT_47   47.0
#  define FLT_48   48.0
#  define FLT_49   49.0
#  define FLT_50   50.0
#  define FLT_51   51.0
#  define FLT_52   52.0
#  define FLT_53   53.0
#  define FLT_54   54.0
#  define FLT_55   55.0
#  define FLT_56   56.0
#  define FLT_57   57.0
#  define FLT_58   58.0
#  define FLT_59   59.0
#  define FLT_60   60.0
#  define FLT_61   61.0
#  define FLT_62   62.0
#  define FLT_63   63.0
#  define FLT_64   64.0
#  define FLT_65   65.0
#  define FLT_66   66.0
#  define FLT_67   67.0
#  define FLT_68   68.0
#  define FLT_69   69.0
#  define FLT_70   70.0
#  define FLT_71   71.0
#  define FLT_72   72.0
#  define FLT_73   73.0
#  define FLT_74   74.0
#  define FLT_75   75.0
#  define FLT_76   76.0
#  define FLT_77   77.0
#  define FLT_78   78.0
#  define FLT_79   79.0
#  define FLT_80   80.0
#  define FLT_81   81.0
#  define FLT_82   82.0
#  define FLT_83   83.0
#  define FLT_84   84.0
#  define FLT_85   85.0
#  define FLT_86   86.0
#  define FLT_87   87.0
#  define FLT_88   88.0
#  define FLT_89   89.0
#  define FLT_90   90.0
#  define FLT_91   91.0
#  define FLT_92   92.0
#  define FLT_93   93.0
#  define FLT_94   94.0
#  define FLT_95   95.0
#  define FLT_96   96.0
#  define FLT_97   97.0
#  define FLT_98   98.0
#  define FLT_99   99.0
#  define FLT_100  100.0

#  define FLT_0_0  0.0
#  define FLT_0_1  0.1
#  define FLT_0_2  0.2
#  define FLT_0_3  0.3
#  define FLT_0_4  0.4
#  define FLT_0_5  0.5
#  define FLT_0_6  0.6
#  define FLT_0_7  0.7
#  define FLT_0_8  0.8
#  define FLT_0_9  0.9

# else

#  define FLT_TYPE float

#  define FLT_0    0.0f
#  define FLT_1    1.0f
#  define FLT_2    2.0f
#  define FLT_3    3.0f
#  define FLT_4    4.0f
#  define FLT_5    5.0f
#  define FLT_6    6.0f
#  define FLT_7    7.0f
#  define FLT_8    8.0f
#  define FLT_9    9.0f
#  define FLT_10   10.0f
#  define FLT_11   11.0f
#  define FLT_12   12.0f
#  define FLT_13   13.0f
#  define FLT_14   14.0f
#  define FLT_15   15.0f
#  define FLT_16   16.0f
#  define FLT_17   17.0f
#  define FLT_18   18.0f
#  define FLT_19   19.0f
#  define FLT_20   20.0f
#  define FLT_21   21.0f
#  define FLT_22   22.0f
#  define FLT_23   23.0f
#  define FLT_24   24.0f
#  define FLT_25   25.0f
#  define FLT_26   26.0f
#  define FLT_27   27.0f
#  define FLT_28   28.0f
#  define FLT_29   29.0f
#  define FLT_30   30.0f
#  define FLT_31   31.0f
#  define FLT_32   32.0f
#  define FLT_33   33.0f
#  define FLT_34   34.0f
#  define FLT_35   35.0f
#  define FLT_36   36.0f
#  define FLT_37   37.0f
#  define FLT_38   38.0f
#  define FLT_39   39.0f
#  define FLT_40   40.0f
#  define FLT_41   41.0f
#  define FLT_42   42.0f
#  define FLT_43   43.0f
#  define FLT_44   44.0f
#  define FLT_45   45.0f
#  define FLT_46   46.0f
#  define FLT_47   47.0f
#  define FLT_48   48.0f
#  define FLT_49   49.0f
#  define FLT_50   50.0f
#  define FLT_51   51.0f
#  define FLT_52   52.0f
#  define FLT_53   53.0f
#  define FLT_54   54.0f
#  define FLT_55   55.0f
#  define FLT_56   56.0f
#  define FLT_57   57.0f
#  define FLT_58   58.0f
#  define FLT_59   59.0f
#  define FLT_60   60.0f
#  define FLT_61   61.0f
#  define FLT_62   62.0f
#  define FLT_63   63.0f
#  define FLT_64   64.0f
#  define FLT_65   65.0f
#  define FLT_66   66.0f
#  define FLT_67   67.0f
#  define FLT_68   68.0f
#  define FLT_69   69.0f
#  define FLT_70   70.0f
#  define FLT_71   71.0f
#  define FLT_72   72.0f
#  define FLT_73   73.0f
#  define FLT_74   74.0f
#  define FLT_75   75.0f
#  define FLT_76   76.0f
#  define FLT_77   77.0f
#  define FLT_78   78.0f
#  define FLT_79   79.0f
#  define FLT_80   80.0f
#  define FLT_81   81.0f
#  define FLT_82   82.0f
#  define FLT_83   83.0f
#  define FLT_84   84.0f
#  define FLT_85   85.0f
#  define FLT_86   86.0f
#  define FLT_87   87.0f
#  define FLT_88   88.0f
#  define FLT_89   89.0f
#  define FLT_90   90.0f
#  define FLT_91   91.0f
#  define FLT_92   92.0f
#  define FLT_93   93.0f
#  define FLT_94   94.0f
#  define FLT_95   95.0f
#  define FLT_96   96.0f
#  define FLT_97   97.0f
#  define FLT_98   98.0f
#  define FLT_99   99.0f
#  define FLT_100  100.0f

#  define FLT_0_0  0.0f
#  define FLT_0_1  0.1f
#  define FLT_0_2  0.2f
#  define FLT_0_3  0.3f
#  define FLT_0_4  0.4f
#  define FLT_0_5  0.5f
#  define FLT_0_6  0.6f
#  define FLT_0_7  0.7f
#  define FLT_0_8  0.8f
#  define FLT_0_9  0.9f

# endif

#endif