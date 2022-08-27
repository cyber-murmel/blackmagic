{ pkgs ? import
    (builtins.fetchGit {
      name = "nixos-22.05-2022_08_27";
      url = "https://github.com/nixos/nixpkgs/";
      ref = "refs/heads/nixos-22.05";
      rev = "f11e12ac6af528c1ba12426ce83cee26f21ceafd";
    })
    { }
}:

with pkgs;
let
  bmp-swlink = (callPackage ./. { inherit pkgs; probe_host = "swlink"; });

  bmp-uart-flash-bootloader = writeScriptBin "bmp-uart-flash-bootloader" ''
    #! ${bash}/bin/bash

    set -euo pipefail

    STM32FLASH_SERIAL=''${1:-/dev/ttyUSB0}

    ${stm32flash}/bin/stm32flash \
      -S 0x8000000 \
      -v -w ${bmp-swlink}/blackmagic_dfu.bin \
      $STM32FLASH_SERIAL
  '';

  bmp-dfu-firmware = writeScriptBin "bmp-dfu-firmware" ''
    #! ${bash}/bin/bash

    set -euo pipefail

    ${dfu-util}/bin/dfu-util -d 1d50:6018,:6017 -s 0x08002000:leave -D ${bmp-swlink}/blackmagic.bin
  '';
in
mkShell {
  buildInputs = import ./packages.nix { inherit pkgs; } ++ [
    bmp-uart-flash-bootloader
    bmp-dfu-firmware
  ];
}
