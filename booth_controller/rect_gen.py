import pandas as pd
import numpy as np


if __name__ == "__main__":
  # write to temp generate file
  with open("temp", "w") as f:
    filename = 'rects.csv'
    data = pd.read_csv(filename)
    # print(data)

    start_ind = data.iloc[:49, 13].tolist()
    rect_len = data.iloc[:49, 12].tolist()
    og_num = data.iloc[:49, 0].tolist()

    temp_str = lambda ind, val1, val2, og_num : \
      f"rects_[{int(ind)}] = Rectangle({int(val1)},{int(val2)});  // rect #{og_num}\n"
    for i in range(len(rect_len)):
        f.write(temp_str(i, start_ind[i], rect_len[i], og_num[i]))
  

  # find start and end positon
  start_line = 0
  end_line = 0 
  i = 0
  with open("lighting_array_controller.cpp", "r") as source_code:
    lines = source_code.readlines()
  with open("lighting_array_controller.cpp", "r") as source_code:
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
  with open("lighting_array_controller.cpp", "w") as source_code:
    i = 0
    for line in lines:
      if (i < start_line or i > end_line):
        source_code.write(line)
      i += 1

  # have to reopen the file because we modified the lines!
  with open("lighting_array_controller.cpp", "r") as source_code:
    lines = source_code.readlines()
  # insert nice new lines
  with open("lighting_array_controller.cpp", "w") as source_code:
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


