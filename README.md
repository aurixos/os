<h1 align="center">
  <a href="https://github.com/aurixos/os">
    <img src="docs/images/logo.png" alt="Logo" width="100" height="100">
  </a>
</h1>

<div align="center">
  AurixOS
  <br />
  <br />
  <a href="https://github.com/aurixos/os/issues/new?assignees=&labels=bug&template=01_BUG_REPORT.md&title=bug%3A+">Report a Bug</a>
  ·
  <a href="https://github.com/aurixos/os/issues/new?assignees=&labels=enhancement&template=02_FEATURE_REQUEST.md&title=feat%3A+">Request a Feature</a>
  .
  <a href="https://github.com/aurixos/os/issues/new?assignees=&labels=question&template=04_SUPPORT_QUESTION.md&title=support%3A+">Ask a Question</a>
</div>
<br />
<div align="center">

[![Project license](https://img.shields.io/github/license/aurixos/os.svg?style=flat-square)](LICENSE)
[![Discord Chat](https://img.shields.io/discord/1234051470182055988)](https://discord.com/invite/hgbZ6wFP4n)
</div>

<details open="open">
<summary>Table of Contents</summary>

- [About](#about)
- [Getting Started](#getting-started)
  - [Prerequisites](#prerequisites)
  - [Building](#building)
- [Running](#running)
- [Support](#support)
- [Contributing](#contributing)
- [Authors & contributors](#authors--contributors)
- [Security](#security)
- [License](#license)
- [Acknowledgements](#acknowledgements)

</details>

---

> [!IMPORTANT]  
> We're currently switching from Limine to our own custom bootloader. To see the progress, please switch to the `x86_64-bootloader` branch.

## About

AurixOS is a general-purpose operating system, meant to take security, performance and usability to the next level.

<!-- 
<details>
<summary>Screenshots</summary>
<br>

|                               Title                               |
| :---------------------------------------------------------------: |
| <img src="docs/images/screenshot.png" title="Title" width="100%"> |
</details>
-->

## Getting Started

Latest official releases of AurixOS are available for download [here](https://github.com/aurixos/os/releases).

### Prerequisites

If you have [Homebrew](https://brew.sh) installed, simply run `brew bundle` to install **all** required build dependencies (incl. packages to build AurixOS for every supported architecture).
Alternatively, read the [Brewfile](Brewfile) in the root of this repository and install the required (and optional) packages manually.

### Building

To build AurixOS, simply run `make` in the root directory of this repository.
To change the build architecture, run `make ARCH=arch`, where `arch` is the target architecture (Default is set to `x86_64`).

Building AurixOS images is also supported with Make recipes:
- `livecd` builds a CD-ROM image (.iso)
- `livehdd` builds a HDD image (.img)

All images reside in the `release/` directory and follow this naming scheme:
`aurixos-live[MEDIA]-[GIT_REV]_[ARCH].iso`

`make help` shows you all available build options

## Running

To run AurixOS on QEMU, run `make run` (optionally, append `ARCH=arch` if you're building/running AurixOS on an architecture other than x86_64).

Alternatively, you can boot AurixOS on a physical machine by running `dd if=release/<usb-image>.img of=/dev/<target USB drive> bs=1M` and booting off of this USB drive.

## Support

If you have any questions, feel free to open a [GitHub issue](https://github.com/aurixos/os/issues/new?assignees=&labels=question&template=04_SUPPORT_QUESTION.md&title=support%3A+).
Alternatively, you can visit us over on out [Discord server](https://discord.com/invite/hgbZ6wFP4n)!

## Contributing

First off, thanks for taking the time to contribute! Contributions are what make the open-source community such an amazing place to learn, inspire, and create. Any contributions you make will benefit everybody else and are **greatly appreciated**.

Please read [our contribution guidelines](docs/CONTRIBUTING.md), and thank you for being involved!

## Authors & contributors

For a full list of all authors and contributors, see [the contributors page](https://github.com/aurixos/os/contributors).

## Security

AurixOS follows good practices of security, but 100% security cannot be assured.
AurixOS is provided **"as is"** without any **warranty**. Use at your own risk.

_For more information and to report security issues, please refer to our [security documentation](docs/SECURITY.md)._

## License

This project is licensed under the **MIT license**.

See [LICENSE](LICENSE) for more information.

## Acknowledgements

- [The Standard C Library by P. J. Plauger](https://www.amazon.com/Standard-C-Library-P-J-Plauger/dp/0131315099)
