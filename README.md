# AQTIVATE Training Workshop: Performance Engineering Lab / General Instructions

## Introduction

The goal of this lab is to practise approaches and strategies for performance engineering, which have been presented during the connected lectures.
This lab focusses on performance analysis and optimisation of a [dense matrix-matrix multiplier](mmul/README.md)

In the next section you will find information on a tools that you are expected to use for this lab.

## Profiling using perf

Run a command and gather performance counter statistics:

```
perf stat [-e <EVENT> | --event=EVENT] <command>
```

List all available event types:

```
perf list
```

### Further reading

- [Linux kernel documentation](https://perf.wiki.kernel.org/index.php/Main_Page)
- [Brendan Gregg's perf examples](https://www.brendangregg.com/perf.html)

## Profiling using Likwid

To use Likwid perform the following steps:

```
ml PDC
export PATH="/cfs/klemming/home/p/pleiter/Public/opt/likwid-5.3.0/bin:${PATH}"
```

### Further reading

- [Likwid web-page](https://hpc.fau.de/research/tools/likwid/)
- [Likwid source code](https://github.com/RRZE-HPC/likwid)
