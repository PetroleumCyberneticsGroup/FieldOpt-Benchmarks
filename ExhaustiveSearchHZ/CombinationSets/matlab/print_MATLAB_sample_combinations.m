% MATLAB script that prints sample permutations using
% nchoosek with k = 2 and n = 4, n = 9 and n = 81

% ===================================================
%
% Definition
% Combination nY uses a YxY grid with Z=Y^2 points.
% We use nchoosek to calculate all possible combinations
% (reverse=equal, no repetitions) between all points in
% the grid.
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
dirn = '../combinations/';
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

% ===================================================
% TEST SPACES

% ---------------------------------------------------
% n002 = uint16(1:2^2);   % 4             | 6
t000 = tic;
C002 = nchoosek(n002,k);
t002 = toc(t000);
fnnn = 'n002';
printC(C002,[fnnn '-M-' host '.sample'],t002,...
	[fnnn 't-M-' host '.sample'],dirn,host,cpu,flog,2,2^2);

% ---------------------------------------------------
% n003 = uint16(1:3^2);   % 9             | 36
t000 = tic;
C003 = nchoosek(n003,k);
t003 = toc(t000);
fnnn = 'n003';
printC(C003,[fnnn '-M-' host '.sample'],t003,...
	[fnnn 't-M-' host '.sample'],dirn,host,cpu,flog,3,3^2);

% ---------------------------------------------------
% n009 = uint16(1:9^2);   % 81            | 3240
t000 = tic;
C009 = nchoosek(n009,k);
t009 = toc(t000);
fnnn = 'n009';
printC(C009,[fnnn '-M-' host '.sample'],t009,...
	[fnnn 't-M-' host '.sample'],dirn,host,cpu,flog,9,9^2);

% ===================================================
% SUBSPACES: 40|80|100

% ---------------------------------------------------
% n040 = uint16(1:40^2);  % 1600      {A} | 1279200   ~=   1.3*1e6
t000 = tic;
C040 = nchoosek(n040,k);
t040 = toc(t000);
fnnn = 'n040';
printC(C040,[fnnn '-M-' host '.sample'],t040,...
	[fnnn 't-M-' host '.sample'],dirn,host,cpu,flog,40,40^2);

% ---------------------------------------------------
% n080 = uint16(1:80^2);  % 6400      {B} | 20476800  ~=  20.5*1e6
t000 = tic;
C080 = nchoosek(n080,k);
t080 = toc(t000);
fnnn = 'n080';
printC(C080,[fnnn '-M-' host '.sample'],t080,...
	[fnnn 't-M-' host '.sample'],dirn,host,cpu,flog,80,80^2);

% ---------------------------------------------------
% n100 = uint16(1:100^2); % 10000     {C} | 49995000  ~=  50.0*1e6
t000 = tic;
C100 = nchoosek(n100,k);
t100 = toc(t000);
fnnn = 'n100';
printC(C100,[fnnn '-M-' host '.sample'],t100,...
	[fnnn 't-M-' host '.sample'],dirn,host,cpu,flog,100,100^2);

% ===================================================
% SUBSPACES: 120|140|160

% ===================================================
% SUBSPACES: 180|190|200

% ---------------------------------------------------
fprintf('%s\n',repmat('=',1,52));
fclose(flog);

% ===================================================
%
function [] = printC(C,fn,t,tn,dirn,host,cpu,flog,n,nn);

	% combinations
	fid = fopen([dirn fn],'w');
	% fprintf('%d %d\n',C'); % print
	fprintf(fid,'%d %d\n',C');
	fclose(fid);

	% time
	str0 = sprintf('%s\n',repmat('-',1,52));
	str1 = sprintf('%s\n',datestr(now));
	str2 = sprintf('Hostname: %s\n',host);
	str3 = sprintf('Processor: %s',cpu);
	str4 = sprintf('Secs: [%7.3f] Mins: [%7.3f]\n', t, t/60);
	str5 = sprintf('n=%d, # of grid points (n^2) = %d\n', n, nn);
	str6 = sprintf('=> # of combinations =  %d = %3.1f\n', ...
		size(C,1), size(C,1)/1e6);

	fns = dir([dirn fn]);
	if fns.bytes < 1e3
		fs = fns.bytes;
		fstr = '%6.0f bytes';
	elseif (fns.bytes > 1e3) && (fns.bytes < 1e6)
		fs = fns.bytes/1e3;
		fstr = '%6.1f kilobytes';
	else
		fs = fns.bytes/1e6;
		fstr = '%6.1f Megabytes';
	end
	str7 = sprintf(['File size: ' fstr '\n'], fs);
	str8 = sprintf('byte/combination ratio: %4.3f \n', ...
		fns.bytes/size(C,1));

	% fid = fopen([dirn tn],'w');
	fprintf(str0);
	fprintf(str1);
	fprintf(str2);
	fprintf(str3)
	fprintf(str4);
	fprintf(str5);
	fprintf(str6);
	fprintf(str7);
	fprintf(str8);

	% fprintf(fid, str0);
	% fprintf(fid, str1);
	% fprintf(fid, str2);
	% fprintf(fid, str3);
	% fprintf(fid, str4);
	% fprintf(fid, str5);
	% fprintf(fid, str6);

	fprintf(flog, str0);
	fprintf(flog, str1);
	fprintf(flog, str2);
	fprintf(flog, str3);
	fprintf(flog, str4);
	fprintf(flog, str5);
	fprintf(flog, str6);
	fprintf(flog, str7);
	fprintf(flog, str8);

	% fclose(fid);

end
