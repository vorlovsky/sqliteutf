import 'package:flutter/material.dart';
import 'package:path/path.dart' as p;
import 'package:path_provider/path_provider.dart';
import 'package:sqlite3/sqlite3.dart';
import 'package:sqliteutf/sqliteutf.dart' as sqliteutf;

void main() async {
  WidgetsFlutterBinding.ensureInitialized();
  sqlite3.ensureExtensionLoaded(
    SqliteExtension.inLibrary(sqliteutf.lib, 'sqlite3_sqliteutf_init'),
  );
  final dir = await getApplicationDocumentsDirectory();
  final dbPath = p.join(dir.path, 'app.db');
  final db = sqlite3.open(dbPath);
  runApp(MyApp(db: db));
}

class MyApp extends StatefulWidget {
  const MyApp({super.key, required this.db});

  final Database db;

  @override
  State<MyApp> createState() => _MyAppState();
}

class _MyAppState extends State<MyApp> {
  @override
  void dispose() {
    widget.db.dispose();
    super.dispose();
  }

  @override
  Widget build(BuildContext context) {
    final str = 'ABC абв ІЇЁ';
    final result = widget.db //
        .select('SELECT lower_utf(\'$str\') as lower, upper_utf(\'$str\') as upper;')
        .first;
    return MaterialApp(
      home: Scaffold(
        appBar: AppBar(
          title: const Text('SQlite UTF'),
        ),
        body: Center(
          child: Column(
            children: [
              Text('Input: $str'),
              Text('Lower: ${result['lower']}'),
              Text('Upper: ${result['upper']}'),
            ],
          ),
        ),
      ),
    );
  }
}
