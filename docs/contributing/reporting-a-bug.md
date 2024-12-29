# Bug reports

Augmented Carpentry is an actively maintained project that we constantly strive
to improve. With a prototype of this size and complexity, bugs may occur. If you
think you have discovered a bug, you can help us by submitting an issue in our
public [issue tracker], following this guide.

A clear, detailed bug report helps everyone in the Augmented Carpentry community work more efficiently. By providing thorough steps to reproduce, clear descriptions, and helpful logs or screenshots, you ensure that issues are addressed and resolved faster—leading to a better experience for all users.

__But first, please do the following things before creating an issue.__

### Upgrade to latest version

Chances are that the bug you discovered was already fixed in a subsequent
version. Thus, before reporting an issue, ensure that you're running the
[latest version] of AC. Please consult our [upgrade guide] to
learn how to upgrade to the latest version.

!!! warning "Bug fixes are not backported"

    Please understand that only bugs that occur in the latest version of
    AC will be addressed. AC is a living prototype that can only be supported to its bleeding edge version.

  [latest version]: https://github.com/ibois-epfl/augmented-carpentry/releases
  [upgrade guide] : ../installation.md

### Search for solutions

Now, before you go through the trouble of creating a bug report that is answered
and closed right away with a link to the relevant documentation section or
another already reported or closed issue or discussion, you can save time for
us and yourself by doing some research:

1.  [Search our documentation] and look for the relevant sections that could
    be related to your problem. If found, make sure that you configured
    everything correctly.

2.  [Search our issue tracker][issue tracker], as another user might already
    have reported the same problem, and there might even be a known workaround
    or fix for it. Thus, no need to create a new issue.

__Keep track of all <u>search terms</u> and <u>relevant links</u>, you'll need
them in the bug report.__[^1]

  [^1]:
    We might be using terminology in our documentation different from yours,
    but we mean the same. When you include the search terms and related links
    in your bug report, you help us to adjust and improve the documentation.

---

At this point, when you still haven't found a solution to your problem, we
encourage you to create an issue because it's now very likely that you
stumbled over something we don't know yet. Read the following section to learn
how to create a complete and helpful bug report.

  [Search our documentation]: ?q=

## Issue template

We have created issue templates to make the bug reporting process as simple as possible and more efficient. Just pick up the one that fits your needs.

- [Bug reports](#bug-reports)
    - [Upgrade to latest version](#upgrade-to-latest-version)
    - [Search for solutions](#search-for-solutions)
  - [Issue template](#issue-template)
    - [Title](#title)
    - [Context optional { #context }](#context-optional--context-)
    - [Bug description](#bug-description)
    - [Steps to reproduce](#steps-to-reproduce)
    - [New machines { #machine }](#new-machines--machine-)

### Title

A good title is short and descriptive. It should be a one-sentence executive
summary of the issue, so the impact and severity of the bug you want to report
can be inferred from the title.

| <!-- --> | Example  |
| -------- | -------- |
| :material-check:{ style="color: #4DB6AC" } __Clear__ | Built-in `typeset` plugin changes precedence of nav title over `h1`
| :material-close:{ style="color: #EF5350" } __Wordy__ | The built-in `typeset` plugin changes the precedence of the nav title over the document headline
| :material-close:{ style="color: #EF5350" } __Unclear__ | Title does not work
| :material-close:{ style="color: #EF5350" } __Useless__ | Help

### Context <small>optional</small> { #context }

Before describing the bug, you can provide additional context for us to
understand what you were trying to achieve. Explain the circumstances
in which you're using Augmented Carpentry, and what you _think_ might be
relevant. Don't write about the bug here.

> __Why this might be helpful__: some errors only manifest in specific settings,
> environments or edge cases, for example, when your are trying to realize a joint whose shape is not integrated in AC yet.

### Bug description

Now, to the bug you want to report. Provide a clear, focused, specific, and
concise summary of the bug you encountered and your scenario of fabrication.

-   __Keep it short and concise__ – if the bug can be precisely explained in one
    or two sentences, perfect. Don't inflate it – maintainers and future users
    will be grateful for having to read less.

-   __Give the most important details__ – include the model of your woodworking or tools' models.

-   __One bug at a time__ – if you encounter several unrelated bugs, please
    create separate issues for them. Don't report them in the same issue, as
    this makes attribution difficult.

---

:material-run-fast: __Stretch goal__ – if you found a workaround or a way to fix
the bug, you can help other users temporarily mitigate the problem before
we maintainers can fix the bug in our code base.

> __Why we need this__: in order for us to understand the problem, we
> need a clear description of it and quantify its impact, which is essential
> for triage and prioritization.

### Steps to reproduce

At this point, you provided us with enough information to understand the bug
and provided us with a reproduction that we could run and inspect. However, when
we run your reproduction, it might not be immediately apparent how we can see
the bug in action.

Thus, please list the specific steps we should follow when running your
reproduction to observe the bug. Keep the steps short and concise, and make sure
not to leave anything out. Use simple language as you would explain it to a
five-year-old, and focus on continuity.

> __Why we need this__: we must know how to navigate your reproduction in order
> to observe the bug, as some bugs only occur at certain viewports or in
> specific conditions.

### New machines { #machine }

If you're reporting a bug that only occurs in a specific computing unit that is not documented or tested in AC in the section [Getting started](../hardware/index.md)


  [issue tracker]: https://github.com/ibois-epfl/augmented-carpentry/issues
