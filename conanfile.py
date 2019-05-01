from conans import ConanFile, CMake, tools

class ExpectedConan(ConanFile):
    name = "expected"
    version = "master"
    license = "CC0-1.0"
    author = "Simon Brand <tartanllama@gmail.com>"
    url = "https://github.com/TartanLlama/expected"
    description = "C++11/14/17 std::expected with functional-style extensions"
    exports_sources = "*"
    no_copy_source = True

    def package(self):
        self.copy('*.hpp', dst='include/tl', src='tl')

    def package_id(self):
        self.info.header_only()
