from conans import ConanFile, CMake, tools
from importlib_metadata import requires


class AiloggerCppConan(ConanFile):
    name = "slogger_cpp"
    version = "0.1"
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

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()


    def package(self):
       cmake = CMake(self)
       cmake.install()

    def package_info(self):
        self.cpp_info.libs = ["slog"]

