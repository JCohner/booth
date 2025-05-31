import sys

import pandas as pd
import numpy as np

def populate_rect_section(fname_prefix: str, rect_start: int, rect_end: int):
  fname = fname_prefix + "lighting_array_controller.cpp"

  '''
  open and write c code to temp file 
  ''' 
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
  
  '''
  open relevant controller cpp file and
  * find start and end positon
  * remove existing code
  * populate with generated code
  '''
  start_line = 0
  end_line = 0 
  i = 0
  with open(fname, "r") as source_code:
    lines = source_code.readlines()
  with open(fname, "r") as source_code:
    for line in lines:
      # print(line)
      if "// setup rectangles" in line:
        start_line = i+1
        print(f"start is: {i}")
      elif "// end of rectangles" in line:
        end_line =i-1
        print(f"end is: {i}")
      i +=1
  # remove existing text in start and end position
  with open(fname, "w") as source_code:
    i = 0
    for line in lines:
      if (i < start_line or i > end_line):
        source_code.write(line)
      i += 1

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
          source_code.write("  // end of rectangles\n")
        else:
          source_code.write(line)
        i += 1


if __name__ == "__main__":
    #print(f"{sys.argv[1]}, {int(sys.argv[2])}, {int(sys.argv[3])}")
    populate_rect_section(sys.argv[1], int(sys.argv[2]), int(sys.argv[3]))
    # populate_rect_section("led_driver/", 29, 49)
    


