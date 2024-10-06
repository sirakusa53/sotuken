SENSOR_DATA = [[451, 811663104, 1623294968, 813631472, -2096755688,
		405823681, -262078964, 1623294727, 101455920, -262094461,
		-131039481, -470270077, -1, -1, -1, 7],
	       [451, 811663104, 406815736, -65027588, 405823681, -1048377844,
		-2080886688, 101703873, 811647363, -2096755688, -32761793,
		-470273952, -1, -1, -1, 7],
	       [456, 811663104, 532775928, 266387964, 1623294726, 101455920,
		266387843, 405831430, -1048377844, 202911840, 101703934,
		2131226751, -4, -1, -1, 255],
	       [436, 811663104, -524157928, -1048377841, 202911840,
		1623294726, 1065613360, 1623325720, 101455920, -262094461,
		1623294727, -14352, -1, -1, 1048575],
	       [436, -262078720, 1623294727, -1048315856, 202911840,
		1623294726, -1048377360, -2096754720, 405823681, 813630988,
		-524188680, -14833, -1, -1, 1048575],
	       [446, -262078720, 406815495, -1048377844, 202911840,
		1623294726, 1065551856, 1623325720, 101455920, 266387843,
		-131047170, -14696061, -1, -1, 1073741823],
	       [436, 811663104, 532775928, -1048377844, 202911840, 1623294726,
		-260110352, 1623294727, 101455920, 266387843, 532775686,
		-14836, -1, -1, 1048575],
	       [441, 811663104, 406815736, 811662860, -2096755688,
		405823681, 266403340, 1623294726, 101455920, 266387843,
		406815494, -474628, -1, -1, 33554431]]
ANSWER =
    [[35, 20],
     [55, 18],
     [45, 10],
     [20, 13],
     [65, 17],
     [80, 21],
     [40, 28],
     [50, 24]]

function validate(i, humidity, temperture) {
    if (humidity != ANSWER[i][0])
	throw "error";
    if (temperture != ANSWER[i][1])
	throw "error";
}

function decode_sensor_data(sensor_data) {
    var data, i, x, len = sensor_data[0];

    data = new Array(len);
    for (i = 0; i < len; i++) {
	if (i % 32 == 0)
	    x = sensor_data[i / 32 + 1];
	data[i] = x & 1;
	x >>= 1;
    }

    return data;
}
    
function get_lengths_from_signal(data) {
  var STATE_INIT_PULL_DOWN        = 1;
  var STATE_INIT_PULL_UP          = 2;
  var STATE_DATA_FIRST_PULL_DOWN  = 3;
  var STATE_DATA_PULL_UP          = 4;
  var STATE_DATA_PULL_DOWN        = 5;

  var state = STATE_INIT_PULL_DOWN;
  var lengths = [];
  var current_length = 0;
  for (var i = 0; i < data.length; i++) {
    var current = data[i];
    current_length += 1;

    if (state == STATE_INIT_PULL_DOWN) {
      if (current == 0) {
        state = STATE_INIT_PULL_UP;
      } else {
        continue;
      }
    }
    if (state == STATE_INIT_PULL_UP) {
      if (current == 1) {
        state = STATE_DATA_FIRST_PULL_DOWN;
      } else {
        continue;
      }
    }
    if (state == STATE_DATA_FIRST_PULL_DOWN) {
      if (current == 0) {
        state = STATE_DATA_PULL_UP;
      } else {
        continue;
      }
    }
    if (state == STATE_DATA_PULL_UP) {
      if (current == 1) {
        current_length = 0;
        state = STATE_DATA_PULL_DOWN;
      } else {
        continue;
      }
    }
    if (state == STATE_DATA_PULL_DOWN) {
      if (current == 0) {
        lengths.push(current_length);
        state = STATE_DATA_PULL_UP;
      } else {
        continue;
      }
    }
  }
  return lengths;
}


function max_len(ary) {
  if (ary.length > 0) {
    var x = ary[0];
    for (var i = 0; i < ary.length; i++) {
      if (x < ary[i]) x = ary[i];
    }
    return x;
  } else {
    return undefined;
  }
}

function min_len(ary) {
  if (ary.length > 0) {
    var x = ary[0];
    for (var i = 0; i < ary.length; i++) {
      if (x > ary[i]) x = ary[i];
    }
    return x;
  } else {
    return undefined;
  }
}

function make_bits_from_lengths(lengths) {
  var shortest_pull_up = min_len(lengths);
  var longest_pull_up = max_len(lengths);
  var halfway = (longest_pull_up + shortest_pull_up) / 2;

  var bits = [];
  for (var i = 0; i < lengths.length; i++) {
    var length = lengths[i];
    var bit = 0;
    if (length > halfway) {
      bit = 1;
    }
    bits.push(bit);
  }
  return bits;
}

function bytes_from_bits(bits) {
  var the_bytes = [];
  var bt = 0;
  for (var i = 0; i < bits.length; i++) {
    bt = bt << 1;
    if (bits[i]) {
      bt = bt | 1;
    } else {
      bt = bt | 0;
    }
    if ((i+1)%8==0) {
      the_bytes.push(bt);
      bt = 0;
    }
  }
  return the_bytes;
}

function parse_signal(data) {
  var lengths = get_lengths_from_signal(data);
  if (lengths.length != 40) {
    throw ("Data not good, skip (length : " + lengths.length + ")");
    return undefined;
  }
  var bits = make_bits_from_lengths(lengths);
  return bytes_from_bits(bits);
}

function main() {
    var i, iteration;
    var data = new Array(8);

    for (i = 0; i < 8; i++)
	data[i] = decode_sensor_data(SENSOR_DATA[i]);

    print("start benchmark");
    for (iteration = 0; iteration < 1000; iteration++)
	for (i = 0; i < 8; i++) {
	    the_bytes = parse_signal(data[i]);
	    validate(i, the_bytes[0], the_bytes[2]);
	}
}

main();


