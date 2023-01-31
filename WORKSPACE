load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")


# Hedron's Compile Commands Extractor for Bazel
# https://github.com/hedronvision/bazel-compile-commands-extractor
http_archive(
    name = "hedron_compile_commands",

    # Replace the commit hash in both places (below) with the latest, rather than using the stale one here.
    # Even better, set up Renovate and let it do the work for you (see "Suggestion: Updates" in the README).
    url = "https://github.com/hedronvision/bazel-compile-commands-extractor/archive/1266d6a25314d165ca78d0061d3399e909b7920e.tar.gz",
    strip_prefix = "bazel-compile-commands-extractor-1266d6a25314d165ca78d0061d3399e909b7920e",
    # When you first run this tool, it'll recommend a sha256 hash to put here with a message like: "DEBUG: Rule 'hedron_compile_commands' indicated that a canonical reproducible form can be obtained by modifying arguments sha256 = ..."
)
load("@hedron_compile_commands//:workspace_setup.bzl", "hedron_compile_commands_setup")
hedron_compile_commands_setup()

http_archive(
  name = "com_google_absl",
  urls = ["https://github.com/abseil/abseil-cpp/archive/b1f792822b8d25e2f954b32dbcee0ddb89631fa9.zip"],
  strip_prefix = "abseil-cpp-b1f792822b8d25e2f954b32dbcee0ddb89631fa9",
  sha256 = "aaa16a72b15d14e0f9a3271bfdca62a528ae2291b5c7ca27bd30d4e959a1b66f",
)

http_archive(
  name = "bazel_skylib",
  urls = ["https://github.com/bazelbuild/bazel-skylib/releases/download/1.2.1/bazel-skylib-1.2.1.tar.gz"],
  sha256 = "f7be3474d42aae265405a592bb7da8e171919d74c16f082a5457840f06054728",
)
