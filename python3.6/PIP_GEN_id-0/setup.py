import cx_Freeze
from cx_Freeze import setup, Executable

setup(name = "PIP_Generator",
      version = "0.9",
      description = "Test build with cx_Freeze",
      executables = [Executable("PIP_GEN_id-0.py")]
      )
