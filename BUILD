cc_library(name="util",
           hdrs=["util.h"],
           srcs=["util.cc"],
          )

cc_binary(name="problem_662",
          srcs=["662.cc"],
          deps=["util"],
          )

cc_binary(name="problem_668",
          srcs=["668.cc"],
          deps=[
            "util",
            "@com_google_absl//absl/log:absl_check"
          ],
          )
