function stegdir_decode(inputPath, outputPath)
%#codegen

    arguments
        inputPath       (1, 1)  string
        outputPath      (1, 1)  string
    end

    dirList = ls(inputPath);

    fout = fopen(outputPath, "wb");

    for iDir = 3:size(dirList, 1)
        blockData = textscan(dirList(iDir, :), "%d_%s");
        blockData_decoded = matlab.net.base64decode(blockData{2}{1});
        fwrite(fout, blockData_decoded, "uint8");
    end

    fclose(fout);
end