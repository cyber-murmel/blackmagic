{ pkgs ? import
    (builtins.fetchGit {
      name = "nixos-22.05-2022_08_27";
      url = "https://github.com/nixos/nixpkgs/";
      ref = "refs/heads/nixos-22.05";
      rev = "f11e12ac6af528c1ba12426ce83cee26f21ceafd";
    })
    { }
, probe_host ? "swlink"
, ...
}:

pkgs.stdenv.mkDerivation rec {
  name = "blackmagic-firmware-${PROBE_HOST}";
  PROBE_HOST = probe_host;
  buildInputs = import ./packages.nix { inherit pkgs; };
  src = ./.;
  preConfigure = ''
    patchShebangs .
  '';
  installPhase = ''
    mkdir -p $out
    cp src/blackmagic.{bin,elf} $out
    cp src/blackmagic_dfu.{bin,elf,hex} $out
  '';
  dontFixup = true;
}
