function [ results ] = represent_all( filename )
%REPRESENT_ALL Summary of this function goes here
%   Detailed explanation goes here

fileID = fopen(filename, 'r');

text = textscan(fileID, '%s', 'Delimiter', '\n')

disp(text{1}{1})

split_str = strsplit(text{1}{1},' ');
number_of_logs = str2num(split_str{2});

real_attacks = cellfun(@str2num, strsplit(text{1}{2}, ','));

number_of_simulations = (length(text{1})-2)/9

x = 1:number_of_logs;

counter = 1;

results = zeros(number_of_simulations, 9);

for i = 3:9:length(text{1})
    
    disp(counter)
    for j = 0:6
        disp(text{1}{i+j})
        prov = strsplit(text{1}{i+j}, ' ');
        results(counter, j+1) = str2num(prov{2});
    end
    disp(' ')
    
    detections_str = strsplit(text{1}{i+7}, ',');
    false_positives_str = strsplit(text{1}{i+8}, ',');
    
    detections = cellfun(@str2num, strsplit(text{1}{i+7}, ','));
    false_positives = cellfun(@str2num, strsplit(text{1}{i+8}, ','));

    plot(x, false_positives./detections, x, (detections-false_positives)./real_attacks)
    axis([0 inf 0 1])
    
    pause
    
    false_positives_str(end)
    
    false_positive = str2num(false_positives_str{end});
    detection = str2num(detections_str{end});
    
    results(counter, 8) = false_positive/detection;
    results(counter, 9) = (detection-false_positive)/real_attacks(end);
    
    counter = counter + 1;
end

