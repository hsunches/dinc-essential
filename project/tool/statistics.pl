#!/usr/bin/perl
use strict;

my $filename = $ARGV[0];
my $count = $ARGV[1];
my $offset = $ARGV[2];

if (!defined $offset) {
	$offset = 0;
}

die "invalid argument\n" if ($offset < 0 or $count <= 0);

my $fh;

open $fh, $ARGV[0] || die "file not found\n";

my @lines = <$fh>;

close $fh;

die "not enough lines\n" if (scalar(@lines) <= $offset + $count);

my @values = @lines[$offset..$offset + $count - 1];
my $max = -(2 ** 64);
my $min = 2 ** 64;
my $sum = 0;

foreach (@values) {
	chomp;
	$max = $_ if ($max < $_);
	$min = $_ if ($min > $_);
	$sum += $_;
}

my $avg = $sum / $count;
my $below_square = 0;
my $below_count = 0;
my $above_square = 0;
my $above_count = 0;

foreach (@values) {
	my $diff = $_ - $avg;

	if ($diff < 0) {
		$below_square += $diff * $diff;
		$below_count++;
	} elsif ($diff > 0) {
		$above_square += $diff * $diff;
		$above_count++;
	}
}

my $below_stddev = ($below_square / $below_count) ** 0.5;
my $above_stddev = ($above_square / $above_count) ** 0.5;

print "max: $max\n";
print "min: $min\n";
print "avg: $avg\n";
print "stddev-: $below_stddev\n";
print "stddev+: $above_stddev\n";
