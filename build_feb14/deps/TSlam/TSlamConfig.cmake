# ===================================================================================
#  TSlam CMake configuration file
#
#             ** File generated automatically, do not modify **
#
#  Usage from an external project:
#    In your CMakeLists.txt, add these lines:
#
#    FIND_PACKAGE(TSlam REQUIRED )
#    TARGET_LINK_LIBRARIES(MY_TARGET_NAME opencv_calib3d;opencv_core;opencv_dnn;opencv_features2d;opencv_flann;opencv_gapi;opencv_highgui;opencv_imgcodecs;opencv_imgproc;opencv_ml;opencv_objdetect;opencv_photo;opencv_stitching;opencv_video;opencv_videoio;opencv_aruco;opencv_barcode;opencv_bgsegm;opencv_bioinspired;opencv_ccalib;opencv_datasets;opencv_dnn_objdetect;opencv_dnn_superres;opencv_dpm;opencv_face;opencv_fuzzy;opencv_hfs;opencv_img_hash;opencv_intensity_transform;opencv_line_descriptor;opencv_mcc;opencv_optflow;opencv_phase_unwrapping;opencv_plot;opencv_quality;opencv_rapid;opencv_reg;opencv_rgbd;opencv_saliency;opencv_shape;opencv_stereo;opencv_structured_light;opencv_superres;opencv_surface_matching;opencv_text;opencv_tracking;opencv_videostab;opencv_wechat_qrcode;opencv_xfeatures2d;opencv_ximgproc;opencv_xobjdetect;opencv_xphoto;/usr/lib/gcc/x86_64-linux-gnu/11/libgomp.so;/usr/lib/x86_64-linux-gnu/libpthread.a;TSlam_fbow;TSlam_aruco;TSlam_stag;TSlam_xflann;TSlam_g2o_stuff;TSlam_g2o_core;TSlam)
#
#    This file will define the following variables:
#      - TSlam_LIBS          : The list of libraries to links against.
#      - TSlam_LIB_DIR       : The directory where lib files are. Calling LINK_DIRECTORIES
#                                with this path is NOT needed.
#      - TSlam_VERSION       : The  version of this PROJECT_NAME build. Example: "1.2.0"
#      - TSlam_VERSION_MAJOR : Major version part of VERSION. Example: "1"
#      - TSlam_VERSION_MINOR : Minor version part of VERSION. Example: "2"
#      - TSlam_VERSION_PATCH : Patch version part of VERSION. Example: "0"
#
# ===================================================================================
INCLUDE_DIRECTORIES("/usr/local/include")
INCLUDE_DIRECTORIES("/usr/local/include/TSlam")
SET(TSlam_INCLUDE_DIRS "/usr/local/include")

LINK_DIRECTORIES("/usr/local/lib")
SET(TSlam_LIB_DIR "/usr/local/lib")
find_package(OpenCV REQUIRED)
INCLUDE_DIRECTORIES(/usr/local/include/opencv4)

SET(TSlam_LIBS opencv_calib3d;opencv_core;opencv_dnn;opencv_features2d;opencv_flann;opencv_gapi;opencv_highgui;opencv_imgcodecs;opencv_imgproc;opencv_ml;opencv_objdetect;opencv_photo;opencv_stitching;opencv_video;opencv_videoio;opencv_calib3d;opencv_core;opencv_dnn;opencv_features2d;opencv_flann;opencv_gapi;opencv_highgui;opencv_imgcodecs;opencv_imgproc;opencv_ml;opencv_objdetect;opencv_photo;opencv_stitching;opencv_video;opencv_videoio;opencv_calib3d;opencv_core;opencv_dnn;opencv_features2d;opencv_flann;opencv_gapi;opencv_highgui;opencv_imgcodecs;opencv_imgproc;opencv_ml;opencv_objdetect;opencv_photo;opencv_stitching;opencv_video;opencv_videoio;/usr/lib/gcc/x86_64-linux-gnu/11/libgomp.so;/usr/lib/x86_64-linux-gnu/libpthread.a;TSlam_fbow;TSlam_aruco;TSlam_stag;TSlam_xflann;TSlam_g2o_stuff;TSlam_g2o_core TSlam)

SET(TSlam_FOUND YES)
SET(TSlam_FOUND "YES")
SET(TSlam_VERSION        1.1.0)
SET(TSlam_VERSION_MAJOR  1)
SET(TSlam_VERSION_MINOR  1)
SET(TSlam_VERSION_PATCH  0)
