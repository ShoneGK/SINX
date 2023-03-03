docker run --rm -it -v "$(pwd)":/root/env sinx-buildenv
rm -r __temp__
sudo qemu-system-x86_64 kernel.iso
echo "Exicution Sucsessful"