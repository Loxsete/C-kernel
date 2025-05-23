#!/bin/sh

if [ "$0" = "$BASH_SOURCE" ] || [ "$0" = "$(realpath "$0")" ]; then
    echo "Script must be runned with source command to apply changes!"
    exit 0
fi

gcc_version=14.1.0
binutils_version=2.44
arch=i686-elf

mkdir toolchain

cd toolchain

echo "Downloading binutils..."
wget https://ftp.gnu.org/gnu/binutils/binutils-$binutils_version.tar.xz
echo "Downloading gcc..."
wget https://ftp.gnu.org/gnu/gcc/gcc-$gcc_version/gcc-$gcc_version.tar.xz

echo "Extracting packages..."
tar -xf binutils-$binutils_version.tar.xz
tar -xf gcc-$gcc_version.tar.xz

mkdir gcc-build
mkdir binutils-build

echo "Setting up enviro vars..."
export TARGET=$arch
export PREFIX="$PWD/$TARGET"
export PATH="$PATH:$PREFIX/bin"

echo "Configuring binutils..."
cd binutils-build
../binutils-$binutils_version/configure --target=$TARGET --prefix=$PREFIX --with-sysroot --disable-nls --disable-werror

echo "Building binutils..."
make -j $(nproc)

echo "Installing binutils..."
make install
echo "Binutils build done!"

echo "Configuring gcc..."
cd ../gcc-build
../gcc-$gcc_version/configure --target=$TARGET --prefix=$PREFIX --disable-nls --enable-languages=c,c++ --without-headers

echo "Building gcc..."
make all-gcc -j $(nproc)
make all-target-libgcc -j $(nproc)

echo "Installing gcc..."
make install-gcc
make install-target-libgcc
echo "Gcc build done!\n"

cd ../..

echo "Note: you need to put bin directory to your PATH file using this command: "

echo "export PATH=\"\$PATH:$PREFIX/bin\"\n"

echo "And also you may need to put this command to your shell rc file, so it will not reset after shell restart"