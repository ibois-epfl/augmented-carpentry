This folder contains the necessary code and data for the evaluation of the Augmented Carpentry project. The employed dataset can be found in the `test_data` folder. The evaluation is performed by running the `main.py` script, which will generate the necessary plots and metrics to evaluate the performance of the AC system. The dataset is also avaialble in the open sourced [Zenodo repository](https://zenodo.org/record/10.5281/zenodo.14610164).

To run the analysis, you need to create a specific conda environment with the necessary dependencies. You can do this by running the following command:

```bash
conda env create -f environment.yml
```

After creating the environment, you can activate it by running:

```bash
conda activate augmented-carpentry
```

Then, you can run the analysis by executing the following command:

```bash
python f:\augmented-carpentry\eval\src\main.py
--paths "[f:\augmented-carpentry\eval\test_data\halfroof, f:\augmented-carpentry\eval\test_data\quarter, f:\augmented-carpentry\eval\test_data\tower_lower, f:\augmented-carpentry\eval\test_data\tower_upper]" --output_path "f:\augmented-carpentry\eval\build"
```

Additionally you can add the following optional arguments:

```bash
usage: main.py [-h] [--paths PATHS] [--output_path OUTPUT_PATH] [--plot_layout PLOT_LAYOUT] [--show]                                                                                    

Evaluate the performance of AC

optional arguments:
  -h, --help            show this help message and exit
  --paths PATHS         path(s) to the directory containing the results. This should be the root containing the a_beams and b_assembly folders. NB: if you have multiple paths, start   
                        with [] and separate them with commas
  --output_path OUTPUT_PATH
                        path to the directory to save the results
  --plot_layout PLOT_LAYOUT
                        layout of the plots in the figure, insert 1x4 or 2x2
  --show                show the plots in the figure before saving
```

In the results folder, you will find the following files: