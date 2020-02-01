import os
import time

def size_human_readable(size):
    KB = 1024
    MB = 1024 * 1024
    GB = 1024 * 1024 * 1024
    TB = 1024 * 1024 * 1024 * 1024
    if 0 <= size < KB:
        return "{} B".format(size)
    elif KB <= size < MB:
        return "{} KB".format(round(size / KB, 2))
    elif MB <= size < GB:
        return "{} MB".format(round(size / MB, 2))
    elif GB <= size < TB:
        return "{} GB".format(round(size / GB, 2))
    else:
        return "{} TB".format(round(size / TB, 2))

def reverse_file(input_filename, blocksize=1024*1024*4):
    """
    input_filename: full path of input file
    blocksize: read block each loop default is 4MB
    output filename is ${input_filename}.rev
    """
    #blocksize = 10
    ticks_start = time.time()
    assert os.path.isfile(input_filename), "{0} not a file".format(input_filename)
    total_size = os.path.getsize(input_filename)
    output_filename = input_filename + ".rev"
    print("input_filename={0} output_filename={1} total_size={2}".format(input_filename, output_filename, size_human_readable(total_size)))
    completed_bytes = 0
    loop_cnt = 0
    with open(input_filename, "rb") as fr:
        with open(output_filename, "wb") as fw:
            while True:
                read_bytes = fr.read(blocksize)
                #print(type(read_bytes))
                read_size = len(read_bytes)
                if read_size > 0:
                    reversed_bytes = bytes(map(lambda b: 0xff & (~b), read_bytes))
                    #print(size_human_readable(len(read_bytes)))
                    fw.write(reversed_bytes)
                    completed_bytes += read_size
                    ticks_now = time.time()
                    if loop_cnt % 10 == 0:
                        print("progress {0} / {1} time consume={2} \r".format(size_human_readable(completed_bytes), size_human_readable(total_size), (ticks_now - ticks_start)), end="")
                else:
                    break
                loop_cnt += 1
    print("reverse {} finished!".format(output_filename))

if __name__ == "__main__":
    reverse_file("./ABP-560-C.mp4")





