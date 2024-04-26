from setuptools import setup, find_packages

setup(
    name="ACPy",
    version="0.4.2",
    packages=find_packages(),
    install_requires=[
        "numpy",
        # other dependencies...
    ],
    description="AugmentedCarpentryPy for the Augmented Carpentry research at IBOIS, EPFL.",
    long_description=open("README.md").read(),
    long_description_content_type="text/markdown",
    author="Andrea Settimi",
    author_email="andrea.settimi@epfl.ch",
    url="https://github.com/ibois-epfl/augmented-carpentry",
    classifiers=[
        "License :: OSI Approved :: MIT License",
        "Programming Language :: Python :: 3",
        "Programming Language :: Python :: 3.9",
    ],
)
