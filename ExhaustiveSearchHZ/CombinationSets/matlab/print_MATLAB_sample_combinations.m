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


% FULLSETS: 57|73|89
n=57;  n057 = uint16(1:n^2 + 72);
n=73;  n073 = uint16(1:n^2 + 64);
n=89;  n089 = uint16(1:n^2 + 56);

% FULLSETS: 105|121|137
n=105; n105 = uint16(1:n^2 + 48);
n=121; n121 = uint16(1:n^2 + 40);
n=137; n137 = uint16(1:n^2 + 32);

% FULLSETS: 153|169|185|201
n=153; n153 = uint16(1:n^2 + 24);
n=169; n169 = uint16(1:n^2 + 16);
n=185; n185 = uint16(1:n^2 + 8);
n=201; n201 = uint16(1:n^2 + 0);

% n_points: 201  np_before:  0  np_after:  0
% n_points: 185  np_before:  8  np_after:  8
% n_points: 169  np_before: 16  np_after: 16
% n_points: 153  np_before: 24  np_after: 24
% n_points: 137  np_before: 32  np_after: 32
% n_points: 121  np_before: 40  np_after: 40
% n_points: 105  np_before: 48  np_after: 48
% n_points:  89  np_before: 56  np_after: 56
% n_points:  73  np_before: 64  np_after: 64
% n_points:  57  np_before: 72  np_after: 72

% n_cells: 50   cell_lims:  6 - 55
% n_cells: 46   cell_lims:  8 - 53
% n_cells: 42   cell_lims: 10 - 51
% n_cells: 38   cell_lims: 12 - 49
% n_cells: 34   cell_lims: 14 - 47
% n_cells: 30   cell_lims: 16 - 45
% n_cells: 26   cell_lims: 18 - 43
% n_cells: 22   cell_lims: 20 - 41
% n_cells: 18   cell_lims: 22 - 39
% n_cells: 14   cell_lims: 24 - 37

% ==================================================================
%  n  | N=n^2 |     Z     |     sz(B)   | sz(KiB) | sz(MiB)|sz(GiB)|
% ------------------------------------------------------------------
%   2 |     4 |         6 |          0  |       0 |    0.0 |   0.0 |
%   3 |     9 |        36 |          0  |       0 |    0.0 |   0.0 |
%   9 |    81 |      3240 |          0  |       0 |    0.0 |   0.0 |
% ------------------------------------------------------------------
%  57 |  3249 |   5276376 |   50939387  |   49745 |   48.6 |   0.0 |
%  73 |  5329 |  14196456 |  138142342  |  134905 |  131.7 |   0.1 |
%  89 |  7921 |  31367160 |  306003631  |  298832 |  291.8 |   0.3 |
% ------------------------------------------------------------------
% 105 | 11025 |  60769800 |  593444674  |  579536 |  566.0 |   0.6 |
% 121 | 14641 | 107172120 | 1047075070  | 1022534 |  998.6 |   1.0 |
% 137 | 18769 | 176128296 | 1721192603  | 1680852 | 1641.5 |   1.6 |
% ------------------------------------------------------------------
% 153 | 23409 | 273978936 | 2677783235  | 2615023 | 2553.7 |   2.5 |
% 169 | 28561 | 407851080 | 3986521113  | 3893087 | 3801.8 |   3.7 |
% 185 | 34225 | 585658200 | 5724768561  | 5590594 | 5459.6 |   5.3 |
% 201 | 40401 | 816100200 | 7977576090  | 7790602 | 7608.0 |   7.4 |
% ==================================================================


% ===========================================================
%  n  | N=n^2 |     Z     |    Z[1e6]  |  cSet  | cSet[1e6] |
% -----------------------------------------------------------
%   2 |     4 |         6 |      0  |         6 |         0 |
%   3 |     9 |        36 |      0  |        30 |         0 |
%   9 |    81 |      3240 |      0  |      3204 |         0 |
% -----------------------------------------------------------
%  57 |  3249 |   5276376 |      5  |   5273136 |         5 |
%  73 |  5329 |  14196456 |     14  |   8920080 |         9 |
%  89 |  7921 |  31367160 |     31  |  17170704 |        17 |
% -----------------------------------------------------------
% 105 | 11025 |  60769800 |     61  |  29402640 |        29 |
% 121 | 14641 | 107172120 |    107  |  46402320 |        46 |
% 137 | 18769 | 176128296 |    176  |  68956176 |        69 |
% -----------------------------------------------------------
% 153 | 23409 | 273978936 |    274  |  97850640 |        98 |
% 169 | 28561 | 407851080 |    408  | 133872144 |       134 |
% 185 | 34225 | 585658200 |    586  | 177807120 |       178 |
% 201 | 40401 | 816100200 |    816  | 230442000 |       230 |
% -----------------------------------------------------------
% sum of cSets:    816
% ===========================================================


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
	% FULLSETS: 57|73|89

	% ---------------------------------------------------
	% n057
	t000 = tic;
	fnnn = 'n057';

	C057 = nchoosek(n057,k); % get combinations
	fn = [dirn fnnn '_mat' '.fSet'];
	fid = fopen(fn,'w'); % print combinations
	fprintf(fid,'%d %d\n',C057');
	fclose(fid);
	printC(C057,toc(t000),fn,host,cpu,flog,57,57^2,k);

	% ---------------------------------------------------
	% n073
	t000 = tic;
	fnnn = 'n073';

	C073 = nchoosek(n073,k); % get combinations
	fn = [dirn fnnn '_mat' '.fSet'];
	fid = fopen(fn,'w'); % print combinations
	fprintf(fid,'%d %d\n',C073');
	fclose(fid);
	printC(C073,toc(t000),fn,host,cpu,flog,73,73^2,k);


	% ---------------------------------------------------
	% n89
	t000 = tic;
	fnnn = 'n089';

	C089 = nchoosek(n089,k); % get combinations
	fn = [dirn fnnn '_mat' '.fSet'];
	fid = fopen(fn,'w'); % print combinations
	fprintf(fid,'%d %d\n',C089');
	fclose(fid);
	printC(C089,toc(t000),fn,host,cpu,flog,89,89^2,k);

end

% ===================================================
% FULLSETS: 105|121|137

% ===================================================
% FULLSETS: 153|169|185|201

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
