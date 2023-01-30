docker run --rm -it -v "$(pwd)":/root/env sfx-buildenv
rm -r __temp__
sudo qemu-system-x86_64 kernel.iso
echo "Exicution Sucsessful"