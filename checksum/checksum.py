def validate_checksum(data):
    checksum = 0
    length = len(data)

    if ((length % 2) != 0):
        print("Error: data length!")
        return -1

    for i in range(0, length - 2, 2):
        checksum += int(data[i:i+2], 16)
    
    checksum = ((checksum ^ 0xffff) + 1 ) & 0xff

    # Another moethod that get the two's complement
    #if checksum % 256 == 0:
    #    checksum = 0
    #else:
    #    checksum = 256 - (checksum % 256)

    ans_checksum = int(data[-2:], 16)
    
    print("Checksum: \n\tAns: 0x{:02X}, Cal: 0x{:02X}".format(ans_checksum, checksum))

    return True if checksum == ans_checksum else False

if __name__ == "__main__":
    data = input("Please input the HEX value (include checksum)"
                 "\nor press Enter to use a default value:\n\t")
    if data == "":
        data = "20000000440085432EE881533E110470CBF2704A2B8AF238F76D8A01671DA8CC194F88F00A"
        print("\t", data)
    
    isPass = validate_checksum(data)

    '''
    index = 0
    block = 0
    isPass = 0
    with open("<filename.hex>", 'rb') as file:
        for line in file.readlines():
            index += 1
            source_data = line.strip()
            data = source_data[1:]

            data = data.strip()

            if data[6:8] != b'00':
                block += 1
                print("line: {}, block: {}, {}".format(index, block, data))

            isPass = validate_checksum(data)
            if not isPass:
                break
    '''
    
    print("{}".format("PASS" if isPass else "FAILED"))
    
    
        
