# Pull Requests

You can contribute to Material for MkDocs by making a [pull request] that
will be reviewed by maintainers and integrated into the main repository when
the changes made are approved. You can contribute bug fixes, changes to the
documentation, new functionality you have developed, or new toolheads and mounts.

[pull request]: https://docs.github.com/en/pull-requests

!!! note "Considering a pull request"

    Before deciding to spend effort on making changes and creating a pull
    request, please discuss what you intend to do. If you are responding to
    what you think might be a bug, please issue a [bug report] first. If you
    intend to work on documentation, create a [documentation issue]. If you
    want to work on a new toolhead or mount, please read the [add new tool].

[bug report]: reporting-a-bug.md
[documentation issue]: reporting-a-docs-issue.md
[add new tool]: add-new-tool.md


### Preparing changes and draft PR


Follow these steps to work on PR for AC:

1. Fork the AC repository by clicking the **Fork** button on the [AC repository](https://github.com/ibois-epfl/augmented-carpentry). Initially, create the pull request **as a draft**. You do this [through the various interfaces that GitHub provides]. Which one you use is entirely up to you. We do not provide specific instructions for using the interfaces as GitHub provide all the information that should be necessary.

[through the various interfaces that GitHub provides]: https://docs.github.com/en/pull-requests/collaborating-with-pull-requests/proposing-changes-to-your-work-with-pull-requests/creating-a-pull-requestClone the repository to your local machine:

    ```console
    git clone --recurse-submodules https://github.com/ibois-epfl/augmented-carpentry.git
    cd augmented-carpentry
    ```

2. Create a new branch for your feature:

    ```console
    git checkout -b my-feature
    ```

3. Add the AC repository as a remote for convinience:

    ```console
    git remote add upstream https://github.com/ibois-epfl/augmented-carpentry
    ```

4. Next you will need to set up your development environment.

5. Work on your featurev by following our [contribution guidelines](../developer-guide/CONTRIBUTING.md). Next, commit your changes:

    ```console
    git add .
    git commit -m "WIP: Add my feature"
    git push origin my-feature
    ```

### Testing and reviewing changes

Before you commit any changes, you should make sure that they work as expected
and do not create any unintended side effects. You should test them on at least
these three [smoke tests]:

- Test by running AC locally, a laptop run it's fine. This test will run anyways in the CI/CD pipeline.

- Test with relevant examples in your fabrication scenario.

[smoke tests]: https://en.wikipedia.org/wiki/Smoke_testing_(software)


### Dos and Don'ts

1. **Don't** just create a pull request with changes that are not explained.

2. **Do** discuss what you intend to do with people in the discussions so that the
   rational for any changes is clear before you write or modify code.

3. **Do** link to the discussion or any issues to provide the context for a pull
   request.

4. **Do** ask questions if you are uncertain about anything.

5. **Do** ask yourself if what you are doing benefits the wider community and
   makes Material for MkDocs a better product.

6. **Do** ask yourself if the cost of making the changes stands in a good
   relation to the benefits they will bring. Some otherwise sensible changes can
   add complexity for comparatively little gain, might break existing behaviour
   or might be brittle when other changes need to be made.

7. **Do** merge in concurrent changes frequently to minimize the chance of
   conflicting changes that may be difficult to resolve.
