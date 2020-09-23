filepath = 'time_series.csv';

detections_matrix = csvread('./v2/det_detections.csv');

%plot(1:length(detections), detections);

%pause

false_positives_matrix = csvread('./v2/det_false_positives.csv');

%plot(1:length(false_positives), false_positives);

%pause

x_axis = detections_matrix(1,:);
detections = detections_matrix(2,:);
false_positives = false_positives_matrix(2,:);

real_detections = detections-false_positives;

rate_fp = false_positives(2:end) ./ detections(2:end);

rate_real_det = real_detections(2:end) ./ detections(2:end);

figure

plot(x_axis(2:end), rate_fp, x_axis(2:end), rate_real_det);

%x_axis = x_axis(2:end);

csvwrite('ratefp.csv',[x_axis(2:end)', rate_fp']);
csvwrite('raterealdet.csv',[x_axis(2:end)',rate_real_det']);