#python2 setup.py sdist bdist_wheel

# For testing
#twine upload --repostitory testpypi dist/*
#pip install --index-url https://test.pypi.org/simple/ --no-deps SM16univin

# For release
#twine upload dist/*
#pip install SM16univin


#with open("README.md", 'r') as f:
#    long_description = f.read()

from setuptools import setup, find_packages
setup(
    name='SM16univin',
    packages=find_packages(),
    version='1.0.1',
    license='MIT',
    description='Library to control Sixteen Analog/Digital Inputs 8-Layer Stackable HAT for Raspberry Pi',
    #long_description=long_description,
    #long_description_content_type="text/markdown",
    author='Sequent Microsystems',
    author_email='olcitu@gmail.com',
    url='https://sequentmicrosystems.com',
    keywords=['industrial', 'raspberry', 'power', '0-10V', 'thermistor'],
    install_requires=[
        "smbus2",
        ],
    classifiers=[
        'Development Status :: 3 - Alpha',
        # Chose either "3 - Alpha", "4 - Beta" or "5 - Production/Stable" as the current state of your package
        'Intended Audience :: Developers',
        'Topic :: Software Development :: Build Tools',
        'License :: OSI Approved :: MIT License',
        'Programming Language :: Python :: 2.7',
        'Programming Language :: Python :: 3',
        'Programming Language :: Python :: 3.4',
        'Programming Language :: Python :: 3.5',
        'Programming Language :: Python :: 3.6',
        'Programming Language :: Python :: 3.7',
        ],
    )
