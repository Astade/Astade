# Astade

## The Model Is the Source

**Model-driven C and C++ development with UML**

Astade is an open-source UML modeling and code-generation tool for C and C++ development. It helps developers maintain the software architecture in a model, generate source code, and implement behavior—including UML state machines.

**Astade is developed entirely using Astade itself. Its complete C++ source code is generated from the model without manual changes to generated files.**

[Website](https://astade.de/) · [Screenshots](https://astade.de/screenshots.html) · [Astade model](https://github.com/Astade/Astade) · [Generated C++ sources](http://dev.astade.de/job/GenerateSource/lastSuccessfulBuild/artifact/) · [Jenkins CI](http://dev.astade.de/) · [Professional support](mailto:t.spitzer@astade.de?subject=Astade%20Professional%20Support)

## Why Astade?

- **Model-first development:** Keep the software structure in the UML model rather than reconstructing it from source code.
- **C and C++ code generation:** Generate source code from the model, including function implementations stored in the model.
- **UML state machines:** Model state-dependent behavior and generate corresponding code.
- **Controlled round-trip:** Bring the implementation code of existing functions back into the model. Astade does **not** claim general-purpose reverse engineering of arbitrary C++ structures.
- **Self-hosting in practice:** Astade itself is developed using Astade. Its complete C++ source code is generated from the model without manual edits to the generated files.
- **Open source and model-driven:** The GitHub repository contains the Astade model. C++ source files are generated from that model rather than maintained as a separate source tree in Git.

## Screenshots

Real screenshots from the [official Astade gallery](https://astade.de/screenshots.html):

| UML diagrams | State machines |
| --- | --- |
| [Browse Astade screenshots](https://astade.de/screenshots.html) | [Browse Astade screenshots](https://astade.de/screenshots.html) |

<!-- Add verified direct image URLs or repository-local image files here to show previews inline. -->

## Development workflow

1. **Model:** Define classes, relationships, and state machines in Astade.
2. **Generate:** Generate C/C++ source code from the model.
3. **Implement:** Develop function bodies; Astade can transfer code from existing functions back into the model.
4. **Regenerate:** Generate the complete source again from the updated model, including the stored function implementations—no manual edits to the generated files are required.
5. **Build and test:** Use the project's build and test infrastructure to validate changes.

The model remains the authoritative source for the software structure **and the stored function implementations**. The generated files are outputs, not files that need to be manually maintained.

## Astade is developed with Astade

**Astade — The Model Is the Source.**

Astade is entirely developed using Astade itself. The UML model contains the application architecture as well as the implementations of its functions. Astade generates the **complete C++ source code** from this model, **without any subsequent manual changes to the generated files**.

This is not merely diagramming or generating class skeletons: the model is the authoritative development artifact for Astade itself. It demonstrates model-driven development in a real software project.

## Repository layout and generated sources

**Important:** Astade is developed with Astade itself. Therefore, the GitHub repository contains the **Astade model**, not a checked-in copy of the generated C++ source files.

The complete C++ source files, including function implementations stored in the model, are generated using Astade. No manual edits to the generated files are needed. To make it easier to obtain the generated code without first running the generator, Jenkins publishes artifacts from the most recent successful `GenerateSource` build:

**[Download generated C++ source artifacts (Jenkins)](http://dev.astade.de/job/GenerateSource/lastSuccessfulBuild/artifact/)**

These are **generated build artifacts**, not the canonical model sources. The `lastSuccessfulBuild` link follows the latest successful build, so its contents may change over time. For reproducibility, record the model revision and the corresponding Jenkins build when using these files.

## Getting started

### Get the Astade model

```bash
git clone https://github.com/Astade/Astade.git
cd Astade
```

This checkout provides the **model**. It does not, by itself, provide a complete set of generated C++ files.

To obtain the C++ sources, either:

1. Generate them from the model using an existing Astade installation, or
2. Download the [generated sources from Jenkins](http://dev.astade.de/job/GenerateSource/lastSuccessfulBuild/artifact/).

Astade can be compiled on current Linux distributions. The precise generation and build steps depend on the toolchain and project configuration; consult the project documentation and build files for the relevant revision.

For introductory examples, see the [`tutorial`](https://github.com/Astade/Astade/tree/master/tutorial) directory, if present in the checked-out revision.

## Continuous integration

Astade uses **Jenkins** for continuous integration.

[Open the Astade Jenkins server](http://dev.astade.de/) · [Latest successful GenerateSource artifacts](http://dev.astade.de/job/GenerateSource/lastSuccessfulBuild/artifact/)

Build and test results should be checked on the CI server; this README does not imply that every platform or revision is currently passing.

## Professional support and custom development

Professional services are available **directly from Thomas Spitzer, the original developer of Astade**.

Services include technical support, troubleshooting, maintenance, custom code-generator development, UML and software-architecture consulting, state-machine development, project integration, and individual enhancements.

**Contact:** [Thomas Spitzer — t.spitzer@astade.de](mailto:t.spitzer@astade.de?subject=Astade%20Professional%20Support)

For commercial support inquiries, please contact Thomas directly. For general project discussions and reproducible bug reports, use the repository's GitHub facilities where appropriate.

## Contributing

Contributions, bug reports, and improvement proposals are welcome. Before making substantial changes, open an issue to discuss the approach and check for existing work.

When reporting a bug, please include the Astade revision, operating system, steps to reproduce, expected behavior, and actual behavior. A minimal model or example is especially helpful.

## License

Astade is open-source software. See the license information included in this repository for the authoritative terms.

---

**Astade — The Model Is the Source.**
