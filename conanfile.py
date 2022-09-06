from conans import ConanFile, CMake, tools
from importlib_metadata import requires


class AiloggerCppConan(ConanFile):
    name = "ailogger_cpp"
    version = "0.1"
    author = "Wang Haojie haojie.wang@upuphone.com"
    description = "AiLog C++"
    settings = "os", "compiler", "build_type", "arch"
    options = {"shared": [True, False], "fPIC": [True, False]}
    default_options = {"shared": False, "fPIC": True}
    requires = "spdlog/1.10.0"
    exports_sources = "CMakeLists.txt", "src/*"
    generators = "cmake"

    def config_options(self):
        if self.settings.os == "Linux":
            del self.options.fPIC
            
    def collect_headers(self, include_folder):
        self.copy("*.h"  , dst="include", src=include_folder)
        self.copy("*.hpp", dst="include", src=include_folder)
        self.copy("*.inl", dst="include", src=include_folder)

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def package(self):
        self.build()
        self.copy("*.h"  , dst="include", keep_path=False)
        self.copy("*.a"  , dst="lib", keep_path=False)
        self.copy("*.so" , dst="lib", keep_path=False)
        self.copy("*.lib", dst="lib", keep_path=False)

    def package_info(self):
        self.cpp_info.libs = ["ailog"]

