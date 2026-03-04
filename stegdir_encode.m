function stegdir_encode(inputPath, outputPath)
%#codegen

    arguments
        inputPath       (1, 1)  string
        outputPath      (1, 1)  string
    end

    % Block size must be such that the folder name length does not exceed
    % the OS limit
    blockSize = 180;
    
    fin = fopen(inputPath, "r");
    
    if ~isfolder(outputPath)
        mkdir(outputPath)
    else
        rmdir(outputPath+filesep+"*")
    end
    
    blkCounter = 0;
    while(1)
        fileData = uint8(fread(fin, blockSize, "uint8"));
        if numel(fileData) == 0
            break
        end
        mkdir(outputPath+filesep+num2str(blkCounter)+"_"+base64Encode(fileData, true))
        blkCounter = blkCounter + 1;
    end

    fclose(fin);
end