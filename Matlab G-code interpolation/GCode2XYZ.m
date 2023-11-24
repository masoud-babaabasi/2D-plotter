%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% GCODE INTERPOLATION:
% --------------------
% Descr.:   example of GCode interpolation to axis path
%           for 3-axis machine tools given path difference
% Author:   Thomas Beauduin, University of Tokyo, 2016
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
clear all; close all; clc;

% Interpolation Parameters:
input = 'Spring.txt';       % input G-Code txt-file
ds = 1e-2;                  % interpolation distance
startPos = [0,0,0];      % cartesian start position

% Main Function:
[path] = GCode2path(input,ds,startPos);

figure;
comet(path(:,1),path(:,2));
    axis equal, rotate3d on
    
% figure;
% subplot(311),plot(path(:,1))
% subplot(312),plot(path(:,2))
%subplot(313),plot(path(:,3))