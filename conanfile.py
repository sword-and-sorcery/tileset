from conans import ConanFile, CMake

class Tileset(ConanFile):
    name = "tileset"
    version = "0.0"

    settings = "os", "arch", "compiler", "build_type"
    options = {"shared": [True, False]}
    default_options = {"shared": False}

    generators = "cmake"

    scm = {"type": "git",
           "url": "auto",
           "revision": "auto"}

    def requirements(self):
        self.requires("rapidxml/1.13@bincrafters/stable", private=True)
        self.requires("boost/1.69.0@conan/stable", private=True)

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()
        cmake.install()

    def package_info(self):
        self.cpp_info.libs = ["tileset",]
