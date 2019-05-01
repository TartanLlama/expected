from conans import ConanFile, CMake, tools

class ExpectedConan(ConanFile):
    name = "expected"
    version = "master"
    license = "CC0-1.0"
    author = "Simon Brand <tartanllama@gmail.com>"
    url = "https://github.com/TartanLlama/expected"
    description = "C++11/14/17 std::expected with functional-style extensions"
    settings = "os", "compiler", "build_type", "arch"
    generators = "cmake"
    exports_sources = "*"

    def source(self):
        tools.replace_in_file('CMakeLists.txt', 'project(tl-expected)',
        '''project(tl-expected)
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()
        ''')

    def configure_cmake(self):
        cmake = CMake(self)
        cmake.configure()
        return cmake

    def build(self):
        cmake = self.configure_cmake()
        cmake.build()

        if not tools.cross_building(self.settings):
            self.run('%s/bin/tests' % self.build_folder)

    def package(self):
        self.copy('*.hpp', dst='include/tl', src='include/tl')