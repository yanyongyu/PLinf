from setuptools import Extension
from Cython.Build import cythonize

extensions = [Extension("*", ["plinf/**/*.pyx"])]


def build(setup_kwargs: dict):
    setup_kwargs.update({
        "ext_modules":
            cythonize(extensions, compiler_directives={"language_level": "3"})
    })
