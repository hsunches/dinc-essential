#!/usr/bin/perl
use strict;
use bigint;
use Switch;
use Config::IniFiles;

print "Content-type: text/plain\r\n\r\n";

my $qs = $ENV{QUERY_STRING};

if ($qs !~ /hal\=(.+)/) {
	print "( ^o^)\n";
	exit 0;
}

my $cfg = Config::IniFiles->new(-file => $ARGV[0] || "din.ini");
my $is_cfg_changed = 0;
my @ids = split(",", $1);

foreach (@ids) {
	my $value;

	switch ($cfg->val($_, "type")) {
		case "fixed" {
			$value = $cfg->val($_, "value");
		}

		case "enum-periodic" {
			my $count = $cfg->val($_, "count");
			my $index = $cfg->val($_, "index");

			$value = $cfg->val($_, "value$index");
			$cfg->setval($_, "index", ($index + 1) % $count);
			$is_cfg_changed = 1;
		}

		case "enum-random" {
			my $count = $cfg->val($_, "count");

			$value = $cfg->val($_, "value".int(rand($count)));
		}

		case "ranged" {
			my $min = $cfg->val($_, "value-min");
			my $max = $cfg->val($_, "value-max");

			$value = $min + int(rand($max - $min + 1));
		}

		case "cumulative" {
			$value = $cfg->val($_, "value");

			my $min = $cfg->val($_, "step-min");
			my $max = $cfg->val($_, "step-max");
			my $value_next = $value + $min + int(rand($max - $min + 1));
			my $value_overflow = 2 ** $cfg->val($_, "value-bits");

			$value_next = $value_next % $value_overflow if ($value_next >= $value_overflow);
			$cfg->setval($_, "value", $value_next);
			$is_cfg_changed = 1;
		}
	}

	print "$value\n";

	if ($cfg->val($_, "dump") == 1) {
		my $fh;

		open $fh, ">>", $cfg->val($_, "name").".log";
		print $fh "$value\n";
		close $fh;
	}
}

if ($is_cfg_changed) {
	$cfg->RewriteConfig();
}
