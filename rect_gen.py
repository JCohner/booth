import sys

import pandas as pd
import numpy as np

def write_rect_values_to_temp(rect_start: int, rect_end: int):
    with open("temp", "w") as f:
        filename = 'rects.csv'
        data = pd.read_csv(filename)
        # print(data)

        '''
        Parse out rectangle length (in LEDs) and its assigned number
        '''
        rect_len = data.iloc[rect_start:rect_end, 12].tolist()
        og_num = data.iloc[rect_start:rect_end, 0].tolist()
        accumulator_ind = 0

        '''
        string builder
        '''
        temp_str = lambda ind, val1, val2, og_num : \
          f"rects_[{int(ind)}] = Rectangle({int(val1)},{int(val2)});  // rect #{og_num}\n"

        for i in range(len(rect_len)):
            f.write(temp_str(i, accumulator_ind, rect_len[i], og_num[i]))
            accumulator_ind += rect_len[i]

def delete_lines_between_flags(fname: str, start_flag: str, end_flag: str):
    start_line = 0
    end_line = 0 
    i = 0
    with open(fname, "r") as source_code:
        lines = source_code.readlines()
    with open(fname, "r") as source_code:
        for line in lines:
            # print(line)
            if start_flag in line:
                start_line = i+1
                print(f"start flag: {start_flag} is at line: {i}")
            elif end_flag in line:
                end_line =i-1
                print(f"end flag: {end_flag} is at line: {i}")
            i +=1
    # remove existing text in start and end position
    with open(fname, "w") as source_code:
        i = 0
        for line in lines:
            if (i < start_line or i > end_line):
                source_code.write(line)
            i += 1
    return start_line

def write_temp_file_between_flags(fname:str, start_line: int, end_flag: str):
  # have to reopen the file because we modified the lines!
  with open(fname, "r") as source_code:
    lines = source_code.readlines()
  # insert nice new lines
  with open(fname, "w") as source_code:
    with open("temp", "r") as temp:
      i = 0
      done = False
      for line in lines:
        if (i > start_line - 1 and not done):
          for new_line in temp.readlines():
            source_code.write("  " + new_line)
            done = True
          source_code.write(f"  // end of rectangles\n")
        else:
          source_code.write(line)
        i += 1


def populate_rect_section(fname_prefix: str, rect_start: int, rect_end: int):
    fname = fname_prefix + "lighting_array_controller.cpp"
    write_rect_values_to_temp(rect_start, rect_end)
    start_line = delete_lines_between_flags(fname, "  // setup rectangles", "  // end of rectangles")
    write_temp_file_between_flags(fname, start_line, "  // end of rectangles")



if __name__ == "__main__":
    populate_rect_section(sys.argv[1], int(sys.argv[2]), int(sys.argv[3]))
    


