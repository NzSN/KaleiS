load("@bazel_tools//tools/build_defs/repo:git.bzl", "new_git_repository")


def _ext_impl(ctx):
    new_git_repository(
        name = "tree_sitter",
        remote = "https://github.com/tree-sitter/tree-sitter.git",
        tag = "v0.24.7",
        build_file_content =
        """
load("@rules_foreign_cc//foreign_cc:make.bzl", "make")
filegroup(
    name = "srcs",
    srcs = glob(["**"]),
)

# External modules
make(
    name = "tree_sitter",
    out_shared_libs = ["libtree-sitter.so.0.24"],
    lib_source = ":srcs",
    includes = ["include"],
    visibility = ["//visibility:public"]
)
        """
    )

    new_git_repository(
        name = "rapidcheck",
        remote = "https://github.com/emil-e/rapidcheck.git",
        branch = "master",
        build_file_content =
        """
load("@rules_foreign_cc//foreign_cc:defs.bzl", "cmake")

filegroup(
    name = "rapidcheck_src",
    srcs = glob(["**"]),
)

cmake(
    name = "rapidcheck",
    lib_source = "rapidcheck_src",
    out_static_libs = ["librapidcheck.a"],
    out_include_dir = "include",
    generate_args = ["-DRC_ENABLE_GTEST=ON"],
    visibility = ["//visibility:public"],
)

        """)


ext = module_extension(
    implementation = _ext_impl
)
