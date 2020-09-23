filepath = '../result_files/time_series.csv';

detections = csvread('../det_detections.csv');

%plot(1:length(detections), detections);

%pause

false_positives = csvread('../det_false_positives.csv');

%plot(1:length(false_positives), false_positives);

%pause

real_detections = detections-false_positives;

rate_fp = false_positives ./ detections;

rate_real_det = real_detections ./ detections;

figure

plot(1:length(rate_fp), rate_fp, 1:length(rate_real_det), rate_real_det);