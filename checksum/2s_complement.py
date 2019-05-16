if __name__ == "__main__":
    data = 5
    _2s_complement = ((data ^ 0xffff) + 1) & 0xff

    print("data: {:3d} -> {}".format(data, bin(data)[2:].zfill(8)))
    print("data: {:3d} -> {}".format(_2s_complement, bin(_2s_complement)[2:].zfill(8)))

    # -5 的補數 11111011, equal: 251
    # another method
    _2s_complement_2 = 256 - (data % 256)
    print("data: {:3d} -> {}".format(_2s_complement_2, bin(_2s_complement_2)[2:].zfill(8)))
