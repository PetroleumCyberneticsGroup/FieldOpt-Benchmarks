% ******************************************************************************
% Copyright (C) 2017 Mathias C. Bellout <mathias.bellout@ntnu.no>

% This file is part of the FieldOpt-Benchmarks project,
% an NTNU Petroleum Cybernetics Group project.

% FieldOpt-Benchmarks is free software: you can redistribute it and/or modify
% it under the terms of the GNU General Public License as published by
% the Free Software Foundation, either version 3 of the License, or
% (at your option) any later version.

% FieldOpt-Benchmarks is distributed in the hope that it will be useful,
% but WITHOUT ANY WARRANTY; without even the implied warranty of
% MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
% GNU General Public License for more details.

% You should have received a copy of the GNU General Public License
% along with FieldOpt-Benchmarks.  If not, see <http://www.gnu.org/licenses/>.
% ******************************************************************************

% MATLAB script that prints sample permutations using
% nchoosek with k = 2 and n = 4, n = 9 and n = 81

% These data are use to check the output of the permutation
% algorithm (for_each_reversible_permutation) used to create
% the full (fSet) and complementary (cSet) data sets.

% ===================================================
%
% Definition
% Combination nY uses a YxY grid with Z=Y^2 points.
% We use nchoosek to calculate all possible combinations
% (reverse=equal, no repetitions) between all points in
% the grid.
% 
% Runtimes and processors used for the different
% combinations are given in separate files.

clc
fprintf('%s\n',repmat('=',1,52));
clear all

% ===================================================
%
cmd_str=['cat /proc/cpuinfo | grep '...
'"model name" -m1 | awk -F ":" ''{print $2}'' '];
[stat cpu] = system(cmd_str);
[stat host] = system('hostname | tr -d ''\n''');
dirn = '../combinations/fSets-matlab/';
flog = fopen([dirn 'runtimes-' host '.txt'],'w');

k = uint16(2);
%                       % # grid points | # combinations
                        % N = n^2       | Z = (N-1)*N/2
% TEST SPACES
n002 = uint16(1:2^2);   % 4             | 6
n003 = uint16(1:3^2);   % 9             | 36
n009 = uint16(1:9^2);   % 81            | 3240
% SUBSPACES: 40|80|100
n040 = uint16(1:40^2);  % 1600      {A} | 1279200   ~=   1.3*1e6
n080 = uint16(1:80^2);  % 6400      {B} | 20476800  ~=  20.5*1e6
n100 = uint16(1:100^2); % 10000     {C} | 49995000  ~=  50.0*1e6
% SUBSPACES: 120|140|160
n120 = uint16(1:120^2); % 14400     {D} | 103672800 ~= 103.7*1e6
n140 = uint16(1:140^2); % 19600     {E} | 192070200 ~= 192.1*1e6
n160 = uint16(1:160^2); % 25600     {F} | 327667200 ~= 327.7*1e6
% SUBSPACES: 180|190|200
n180 = uint16(1:180^2); % 32400     {G} | 524863800 ~= 524.9*1e6
n190 = uint16(1:190^2); % 36100     {H} | 651586950 ~= 651.6*1e6
n200 = uint16(1:200^2); % 40000     {I} | 799980000 ~= 800.0*1e6

% {Is} = {I} - {H} = 800.0 - 651.6 = 148.4
% {Hs} = {H} - {G} = 651.6 - 524.9 = 126.7
% {Gs} = {G} - {F} = 524.9 - 327.7 = 197.2

% {Fs} = {F} - {E} = 327.7 - 192.1 = 135.6
% {Es} = {E} - {D} = 192.1 - 103.7 =  88.4
% {Ds} = {D} - {C} = 103.7 -  50.0 =  53.7

% {Cs} = {C} - {B} =  50.0 -  20.5 =  29.5
% {Bs} = {B} - {A} =  20.5 -  1.3  =  19.2
% {As} = {A}                       =   1.3

% {Is}  + {Hs}  + {Gs}  + {Fs}  + {Es} + {Ds} + {Cs} + {Bs} + {As} =
% 148.4 + 126.7 + 197.2 + 135.6 + 88.4 + 53.7 + 29.5 + 19.2 + 1.3 = 800

run_test_space = true;
run_sub_spaces = true;

if run_test_space

	% ===================================================
	% TEST SPACES

	% ---------------------------------------------------
	% n002 = uint16(1:2^2);   % 4             | 6
	t000 = tic;
	fnnn = 'n002';

	C002 = nchoosek(n002,k); % get combinations
	fn = [dirn fnnn '_mat' '.fSet'];
	fid = fopen(fn,'w'); % print combinations
	fprintf(fid,'%d %d\n',C002');
	fclose(fid);	
	printC(C002,toc(t000),fn,host,cpu,flog,2,2^2,k);

	% ---------------------------------------------------
	% n003 = uint16(1:3^2);   % 9             | 36
	t000 = tic;
	fnnn = 'n003';

	C003 = nchoosek(n003,k); % get combinations
	fn = [dirn fnnn '_mat' '.fSet'];
	fid = fopen(fn,'w'); % print combinations
	fprintf(fid,'%d %d\n',C003');
	fclose(fid);	
	printC(C003,toc(t000),fn,host,cpu,flog,3,3^2,k);

	% ---------------------------------------------------
	% n009 = uint16(1:9^2);   % 81            | 3240
	t000 = tic;
	fnnn = 'n009';

	C009 = nchoosek(n009,k); % get combinations
	fn = [dirn fnnn '_mat' '.fSet'];
	fid = fopen(fn,'w'); % print combinations
	fprintf(fid,'%d %d\n',C009');
	fclose(fid);	
	printC(C009,toc(t000),fn,host,cpu,flog,9,9^2,k);

end

if run_sub_spaces

	% ===================================================
	% SUBSPACES: 40|80|100

	% ---------------------------------------------------
	% n040 = uint16(1:40^2);  % 1600      {A} | 1279200   ~=   1.3*1e6
	t000 = tic;
	fnnn = 'n040';

	C040 = nchoosek(n040,k); % get combinations
	fn = [dirn fnnn '_mat' '.fSet'];
	fid = fopen(fn,'w'); % print combinations
	fprintf(fid,'%d %d\n',C040');
	fclose(fid);	
	printC(C040,toc(t000),fn,host,cpu,flog,40,40^2,k);

	% ---------------------------------------------------
	% n080 = uint16(1:80^2);  % 6400      {B} | 20476800  ~=  20.5*1e6
	t000 = tic;	
	fnnn = 'n080';

	C080 = nchoosek(n080,k); % get combinations
	fn = [dirn fnnn '_mat' '.fSet'];
	fid = fopen(fn,'w'); % print combinations
	fprintf(fid,'%d %d\n',C080');
	fclose(fid);	
	printC(C080,toc(t000),fn,host,cpu,flog,80,80^2,k);


	% ---------------------------------------------------
	% n100 = uint16(1:100^2); % 10000     {C} | 49995000  ~=  50.0*1e6
	t000 = tic;	
	fnnn = 'n100';

	C100 = nchoosek(n100,k); % get combinations
	fn = [dirn fnnn '_mat' '.fSet'];
	fid = fopen(fn,'w'); % print combinations
	fprintf(fid,'%d %d\n',C100');
	fclose(fid);	
	printC(C100,toc(t000),fn,host,cpu,flog,100,100^2,k);

end

% ===================================================
% SUBSPACES: 120|140|160

% ===================================================
% SUBSPACES: 180|190|200

% ---------------------------------------------------
fprintf('%s\n',repmat('=',1,52));
fclose(flog);




% ===================================================
%
function [] = printC(C,t,fn,host,cpu,flog,n,N,k);

	% time string, hostname, processor type
	str0 = sprintf('[MATLAB]%s\n',repmat('-',1,52));
	str1 = sprintf('%s\n',datestr(now, 'ddd dd.mm.yyyy HH:MM:SS'));
	str2 = sprintf('Hostname: %s\n',host);
	str3 = sprintf('Processor: %s',cpu);

	% selection, sampling size, # of combinations
	str4 = sprintf('Selection, r = %d\n', k);
	str5 = sprintf('Sampling grid (1D), n = %d\n', n);
	str6 = sprintf('Sampling grid (2D), N = n^2 = %d\n', N);
	str7 = sprintf(['# of combinations (reverse), '...
		'Z = (N-1)*N/2 = %d = %5.3E\n'], size(C,1), size(C,1));

	% file size
	fns = dir(fn);
	fs_B = fns.bytes;
	fs_KiB = fns.bytes/1024;
	fs_MiB = fns.bytes/1024^2;
	fs_GiB = fns.bytes/1024^3;
	str8 = sprintf(['File size:\n' ...
		 '%10d bytes(B)\n' ...
		 '%10.1f KiB \n' ...
		 '%10.1f MiB \n' ...
		 '%10.1f GiB \n' ...
		 ], fs_B, fs_KiB, fs_MiB, fs_GiB);

	% runtime
	t_ms = t*1e3;
	t_s  = t;
	t_m  = t/60;
	t_h  = t/60/60;
	t_d  = t/60/60/24;
	str9 = sprintf(['Elapsed time:\n' ...
		 '%10.1f milliseconds\n' ...
		 '%10.1f seconds\n' ...
		 '%10.1f minutes\n' ...
		 '%10.1f hours\n' ...
		 '%10.1f days\n' ...
		 ], t_ms, t_s, t_m, t_h, t_d);

	str10 = sprintf('byte/combination ratio: %4.3f \n', ...
		fns.bytes/size(C,1));

	fprintf(str0);
	fprintf(str1);
	fprintf(str2);
	fprintf(str3)
	fprintf(str4);
	fprintf(str5);
	fprintf(str6);
	fprintf(str7);
	fprintf(str8);
	fprintf(str9);
	fprintf(str10);

	fprintf(flog, str0);
	fprintf(flog, str1);
	fprintf(flog, str2);
	fprintf(flog, str3);
	fprintf(flog, str4);
	fprintf(flog, str5);
	fprintf(flog, str6);
	fprintf(flog, str7);
	fprintf(flog, str8);
	fprintf(flog, str9);
	fprintf(flog, str10);

end
