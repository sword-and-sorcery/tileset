from conans import ConanFile, CMake

class Tileset(ConanFile):
    name = "ui-tileset"
    version = "0.0"

    settings = "os", "arch", "compiler", "build_type"
    options = {"shared": [True, False]}
    default_options = {"shared": False}

    generators = "cmake"

    scm = {"type": "git",
           "url": "auto",
           "revision": "auto"}

    def requirements(self):
        # TODO: Conan, default_options are not being assigned yet
        rapidxml_shared = self.options["rapidxml"].shared
        boost_shared = self.options["boost"].shared
        
        public_boost = boost_shared or boost_shared is None
        public_rapidxml = rapidxml_shared or rapidxml_shared is None
        
        self.output.info("Require rapidxml public {}".format(public_boost))
        self.output.info("Require boost public {}".format(public_rapidxml))

        self.requires("rapidxml/1.13@bincrafters/stable", private=not public_boost)
        self.requires("boost/1.69.0@conan/stable", private=not public_rapidxml)

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()
        cmake.install()

    def package_info(self):
        self.cpp_info.libs = ["tileset",]
