# Text for Everyone

> Because if text works well in one of the most popular systems programming languages, the entire world over can start to benefit properly.

This repository is an implementation of an up and coming proposal percolating through SG16, [P1629 - Standard Text Encoding](https://thephd.github.io/vendor/future_cxx/papers/d1629.html). It will also include implementations of some downstream ideas covered in Previous Work in this area, including Zach Laine's [Boost.Text (proposed)](https://github.com/tzlaine/text), Robot M. Fernandes's [libogonek](https://github.com/libogonek/ogonek), and Tom Honermann's [text_view](https://github.com/tahonermann/text_view).

Using advances from `std::ranges` and other foundational changes made in C++20, this library is going to produce a flexible, backwards-compatible implementation that can compete with the fast implementations already found in Mozilla Firefox, Chrome, Qt and more.



# Presentations

This work has been presented about and talked about before. See:

- Wednesday, March 7th, 2018 - A Rudimentary Unicode Abstraction
  - [Slides](docs/presentations/2018.03.07%20-%20a%20rudimentary%20unicode%20abstraction%20-%20ThePhD%20-%20SG16%202018.pdf)
- Friday, September 20th, 2018 - Catching ⬆️ - The (Baseline) Unicode Plan for C++23 - ThePhD
  - Video (To be posted on YouTube in the CppCon Channel, soon)
  - [Abstract](https://cppcon2019.sched.com/event/7823aebeede8d50e1daa70b5c22ab0a4)
  - [Slides](docs/presentations/2019.09.20%20-%20Catching%20⬆️%20-%20The%20(Baseline)%20Unicode%20Plan%20for%20C++23%20-%20ThePhD%20-%20CppCon%202019.pdf)



# Current Plans

The current roadmap is to obtain funding to make [the current goals](docs/funding/2019.09.21%20-%20Towards%20Text%20in%20the%20Standard%20Library%20-%20ThePhD.pdf) viable in time for standardization for C++23.

Please considering sponsoring the work via [GitHub Sponsors](https://github.com/users/ThePhD/sponsorship) or [other avenues](https://thephd.github.io/support/) so that this can be finished to allow [Study Group 16 - Unicode](https://github.com/sg16-unicode/sg16) to further support for additional, groundbreaking Unicode facilities in the C++ Standard Library.



# Contributions and Conduct

Anyone filing issues or thinking of making a contribution should be sure to read and thoroughly understand the required [Conduct](CONDUCT.md).

All Contributions are subject to a [Contributor License Agreement](LICENSE.CLA).



# Licenses

This library is currently **dual-licensed**:

- Non-Commercial use falls under the [GNU GPL v3](LICENSE).
- Commercial use falls under a separate Corporate License when entities cannot fulfill the requirements of the GNU GPL v3. Please contact JeanHeyd Meneide ([phdofthehouse@gmail.com](phdofthehouse@gmail.com)) for further inquiry.
